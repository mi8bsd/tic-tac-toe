#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char winner);

int main()
{
    char winner = ' ';
    char response = ' ';

    srand(time(0));

    do
    {
        winner = ' ';
        response = ' ';
        resetBoard();

        while(winner == ' ' && checkFreeSpaces() != 0)
        {
            printBoard();
            playerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0)
                break;

            computerMove();
            winner = checkWinner();
        }

        printBoard();
        printWinner(winner);

        printf("\nPlay again? (Y/N): ");
        scanf(" %c", &response);
    } while(response == 'Y' || response == 'y');

    return 0;
}

//---------------------------

void resetBoard()
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            board[i][j] = ' ';
}

void printBoard()
{
    printf("\n");
    for(int i=0;i<3;i++)
    {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if(i!=2) printf("\n---|---|---\n");
    }
    printf("\n\n");
}

int checkFreeSpaces()
{
    int freeSpaces = 9;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j] != ' ')
                freeSpaces--;

    return freeSpaces;
}

void playerMove()
{
    int x, y;

    do
    {
        printf("Enter row (1-3) and column (1-3): ");
        scanf("%d %d", &x, &y);
        x--; y--;

        if(board[x][y] != ' ')
            printf("Invalid move!\n");

    } while(board[x][y] != ' ');

    board[x][y] = PLAYER;
}

void computerMove()
{
    // Try to win
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            if(board[i][j] == ' ')
            {
                board[i][j] = COMPUTER;
                if(checkWinner() == COMPUTER) return;
                board[i][j] = ' ';
            }
        }

    // Try to block player
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            if(board[i][j] == ' ')
            {
                board[i][j] = PLAYER;
                if(checkWinner() == PLAYER)
                {
                    board[i][j] = COMPUTER;
                    return;
                }
                board[i][j] = ' ';
            }
        }

    // Pick random
    int x, y;
    do
    {
        x = rand() % 3;
        y = rand() % 3;
    } while(board[x][y] != ' ');

    board[x][y] = COMPUTER;
}

char checkWinner()
{
    // Rows
    for(int i=0;i<3;i++)
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
            return board[i][0];

    // Columns
    for(int i=0;i<3;i++)
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];

    // Diagonals
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
        return board[0][0];

    if(board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    return ' ';
}

void printWinner(char winner)
{
    if(winner == PLAYER)
        printf("🎉 YOU WIN!\n");
    else if(winner == COMPUTER)
        printf("💻 COMPUTER WINS!\n");
    else
        printf("😐 IT'S A DRAW!\n");
}
