// includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// prototypes
void cpuTurn(char*, char);
void playerTurn(char*, char);
void drawField(char*);
int isEnd();
void printStats();

int main() {
    srand(time(NULL)); // initializing

    int priority = rand() % 2 + 1;  // generating a random number between 1 and 2
    int turns_number = 1;           // initializing turns number variables
    char field[9] = {};             // initializing a field array

    while (!isEnd())
    {
        if (priority == 1)              // player first
        {
            drawField(field);           // drawing a field
            playerTurn(field, 'x');
            if (isEnd())
                break;
            cpuTurn(field, 'o');
        }
        else if (priority == 2)         // cpu first
        {
            cpuTurn(field, 'x');
            if (isEnd())
                break;
            drawField(field);           // drawing a field
            playerTurn(field, 'o');
        }

        turns_number++;             // increasing number of turns
    }

    printStats();           // printing stats after game
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
        else
        {
            field[fieldNum-1] = sign;
            return;
        }
    }
}
