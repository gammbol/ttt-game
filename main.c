// includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum GAME_STATUS {
    TIE, WIN, LOSE
};

void fieldInit(char*);
void playGame();
void cpuTurn(char*, char);
void playerTurn(char*, char);
void drawField(const char*);
int isEnd(const char*);
int isFull(const char*);
void endGame(enum GAME_STATUS, int);

int main()
{
    char playAgain = 'n';

    srand(time(NULL));

    while (1)
    {
        playGame();

        while (1)
        {
            printf("Wanna play again? (y/N): ");
            scanf(" %c", &playAgain);

            if (playAgain == 'y' || playAgain == 'Y')
                break;
            if (playAgain == 'n' || playAgain == 'N')
            {
                printf("Thank you for playing!\n");
                exit(0);
            }

            printf("Sorry, didn't catch it right!\nPlease choose 'y' or 'n'!\n\n");
        }
    }
}

void fieldInit(char* field)
{
    for (int i = 0; i < 9; i++)
        field[i] = ' ';
}

void playGame()
{
    char sign = 'x';
    char field[9] = {};
    int turns_count = 0;
    fieldInit(field);

    while (1)
    {
        turns_count++;
        drawField(field);
        playerTurn(field, sign);

        if (isEnd(field))
        {
            drawField(field);
            endGame(WIN, turns_count);
            return;
        }
        else if (isFull(field))
        {
            drawField(field);
            endGame(TIE, turns_count);
            return;
        }

        sign = (sign == 'x') ? 'o' : 'x';
        cpuTurn(field, sign);

        if (isEnd(field))
        {
            drawField(field);
            endGame(LOSE, turns_count);
            return;
        }
        else if (isFull(field))
        {
            drawField(field);
            endGame(TIE, turns_count);
            return;
        }

        sign = (sign == 'x') ? 'o' : 'x';
    }
}

void drawField(const char* field)
{
    printf("\n");
    for (int i = 0 ; i < 9; i += 3)
    {
        printf("     *     *     \n");
        printf("  %c  *  %c  *  %c  \n", field[i], field[i+1], field[i+2]);
        printf("     *     *     \n");
        if (i+3 < 9) {
            printf("* * * * * * * * *\n");
        }
    }
    printf("\n");
}

void playerTurn(char* field, char sign)
{
    int cell;
    while (1)
    {
        printf("Enter the number of cell: ");
        scanf(" %d", &cell);

        if (field[cell-1] != ' ')
        {
            printf("The cell is busy!\n");
            continue;
        }
        field[cell-1] = sign;
        return;
    }
}

void cpuTurn(char* field, char sign)
{
    int cell = rand() % 9;

    while (field[cell] != ' ')
        cell = rand() % 9;

    field[cell] = sign;
}

int isFull(const char* field)
{
    for (int i = 0; i < 9; i++)
    {
        if (field[i] == ' ')
            return 0;
    }
    return 1;
}

int isEnd(const char* field)
{
    if (
            (field[0] == field[1] && field[0] == field[2] && field[0] != ' ') ||
            (field[3] == field[4] && field[3] == field[5] && field[3] != ' ') ||
            (field[6] == field[7] && field[6] == field[8] && field[6] != ' ') ||
            (field[0] == field[3] && field[0] == field[6] && field[0] != ' ') ||
            (field[1] == field[4] && field[1] == field[7] && field[1] != ' ') ||
            (field[2] == field[5] && field[2] == field[8] && field[2] != ' ') ||
            (field[0] == field[4] && field[0] == field[8] && field[0] != ' ') ||
            (field[2] == field[4] && field[2] == field[6] && field[2] != ' ')
       )
    {
        return 1;
    }
    return 0;
}

void endGame(enum GAME_STATUS gs, int tc)
{
    if (gs == WIN)
        printf("You won!\n");
    if (gs == LOSE)
        printf("You lost!\n");
    if (gs == TIE)
        printf("Tie!\n");

    printf("Turns: %d\n\n", tc);
}