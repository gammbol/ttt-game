// includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// prototypes
void cpuTurn(char*, char);
void playerTurn(char*, char);
void drawField(const char*);
int isEnd(const char*);
void printStats(int, char, int);
void playGame();
void fieldInit(char*);

int main() {
    char play_again;

    while (1)
    {
        playGame();
        printf("\n\nWanna play again? (y/N): ");
        scanf("%c", &play_again);

        if (play_again == 'n' || play_again == 'N')
        {
            printf("Goodbye!\n");
            exit(0);
        }
    }
}

void fieldInit(char* field)
{
    for (int i = 0; i < 9; i++)
        field[i] = ' ';
}

void playerTurn(char* field, char sign)
{
    int fieldNum;

    while (1)
    {
        printf("Enter a field number: ");
        scanf("%d", &fieldNum);

        if (fieldNum < 1 || fieldNum > 9)
        {
            printf("Please enter a valid number (1-9)!\n");
        }
        else if (field[fieldNum-1] != ' ')
        {
            printf("This cell is busy!\n");
            continue;
        }
        else
        {
            field[fieldNum-1] = sign;
            return;
        }
    }
}

void cpuTurn(char* field, char sign)
{
    while (1)
    {
        int rand_cell = rand() % 9;

        if (field[rand_cell] == 'x' || field[rand_cell] == 'o')
            continue;
        else
        {
            field[rand_cell] = sign;
            return;
        }
    }
}

void printStats(int prior, char sign, int turns_count)
{
    if (prior == 1)
        printf("%s\n", (sign == 'x' ? "You won!" : "You lose!"));
    else if (prior == 2)
        printf("%s\n", (sign == 'x' ? "You lose!" : "You won!"));

    printf("Turns count: %d\n", turns_count);
    printf("Thanks for playing!\n");
}

void playGame()
{
    srand(time(NULL)); // initializing

    int priority = rand() % 2 + 1;  // generating a random number between 1 and 2
    int turns_count = 1;           // initializing turns number variables
    char field[9] = {};             // initializing a field array
    char sign = 'x';                // first sign is always 'x'

    fieldInit(field);

    while (!isEnd(field))
    {
        if (priority == 1)              // player first
        {
            drawField(field);           // drawing a field
            playerTurn(field, sign);
            if (isEnd(field))
            {
                printStats(priority, sign, turns_count);
                return;
            }
            sign = sign == 'x' ? 'o' : 'x';
            cpuTurn(field, sign);
            if (isEnd(field))
            {
                printStats(priority, sign, turns_count);
                return;
            }
            sign = sign == 'x' ? 'o' : 'x';
        }
        else if (priority == 2)         // cpu first
        {
            cpuTurn(field, sign);
            if (isEnd(field))
            {
                printStats(priority, sign, turns_count);
                return;
            }
            sign = sign == 'x' ? 'o' : 'x';
            drawField(field);           // drawing a field
            playerTurn(field,  sign);
            if (isEnd(field))
            {
                printStats(priority, sign, turns_count);
                return;
            }
            sign = sign == 'x' ? 'o' : 'x';
        }

        turns_count++;             // increasing number of turns
    }

    printStats(priority, sign, turns_count);
}

int fieldNotEmpty(const char* field)
{
    for (int i = 0; i < 9; i++)
        if (field[i] == 'x')
            return 1;
    return 0;
}

int isEnd(const char* field)
{
    if (((field[0] == field[1] == field[2]) ||
            (field[3] == field[4] == field[5]) ||
            (field[6] == field[7] == field[8]) ||
            (field[0] == field[3] == field[6]) ||
            (field[1] == field[4] == field[7]) ||
            (field[2] == field[5] == field[8]) ||
            (field[0] == field[4] == field[8]) ||
            (field[2] == field[4] == field[6])) &&
        fieldNotEmpty(field)
        )
    {
        return 1;
    }
    return 0;
}

void drawField(const char* field)
{
    printf("     *     *     \n");
    printf("  %c  *  %c  *  %c  \n", field[0], field[1], field[2]);
    printf("     *     *     \n");
    printf("****************\n");
    printf("     *     *     \n");
    printf("  %c  *  %c  *  %c  \n", field[3], field[4], field[5]);
    printf("     *     *     \n");
    printf("****************\n");
    printf("     *     *     \n");
    printf("  %c  *  %c  *  %c  \n", field[6], field[7], field[8]);
    printf("     *     *     \n");
}