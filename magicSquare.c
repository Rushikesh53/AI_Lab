#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int board[3][3];
int magicSquare[3][3] = {{2, 7, 6}, {9, 5, 1}, {4, 3, 8}};

// Function prototypes
void resetBoard();
void drawBoard();
int isMagicSquare();
int isValidMove(int row, int col);
void makeMove(int row, int col, int player);
int checkWin(int player);
int isBoardFull();
int getComputerMove();

void drawBoard()
{
    // Print the current state of the board
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf(" %c ", (board[i][j] == 1) ? 'X' : ((board[i][j] == 2) ? 'O' : ' '));
            if (j < 2)
                printf("|");
        }
        printf("\n");
        if (i < 2)
            printf("-----------\n");
    }
}
void resetBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = 0;
        }
    }
}

int isMagicSquare()
{
    int sum = 0;

    // Check rows and columns
    for (int i = 0; i < 3; i++)
    {
        int rowSum = 0;
        int colSum = 0;
        for (int j = 0; j < 3; j++)
        {
            rowSum += board[i][j];
            colSum += board[j][i];
        }
        if (rowSum != 15 || colSum != 15)
        {
            return 0;
        }
    }

    // Check diagonals
    int diagSum1 = board[0][0] + board[1][1] + board[2][2];
    int diagSum2 = board[0][2] + board[1][1] + board[2][0];
    if (diagSum1 != 15 || diagSum2 != 15)
    {
        return 0;
    }

    return 1;
}

int isValidMove(int row, int col)
{
    // Check if the move player has played is valid or not
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == 0)
    {
        return 1; // Valid move
    }
    return 0; // Invalid move
}

void makeMove(int row, int col, int player)
{
    // Make move on the board
    board[row][col] = player;
}

int checkWin(int player)
{
    // checking the winning using Magic Square method
    int playerSum;

    // Check rows
    for (int i = 0; i < 3; i++)
    {
        playerSum = 0;
        for (int j = 0; j < 3; j++)
        {
            playerSum += (board[i][j] == player) ? magicSquare[i][j] : 0;
        }
        if (playerSum == 15)
            return 1; // Win
    }

    // Check columns
    for (int j = 0; j < 3; j++)
    {
        playerSum = 0;
        for (int i = 0; i < 3; i++)
        {
            playerSum += (board[i][j] == player) ? magicSquare[i][j] : 0;
        }
        if (playerSum == 15)
            return 1; // Win
    }

    // Check diagonals
    playerSum = 0;
    for (int i = 0; i < 3; i++)
    {
        playerSum += (board[i][i] == player) ? magicSquare[i][i] : 0;
    }
    if (playerSum == 15)
        return 1; // Win

    playerSum = 0;
    for (int i = 0; i < 3; i++)
    {
        playerSum += (board[i][2 - i] == player) ? magicSquare[i][2 - i] : 0;
    }
    if (playerSum == 15)
        return 1; // Win

    return 0; // No win
}

int isBoardFull()
{
    // Check if the board is full or not
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
            {
                return 0; // Board is not full
            }
        }
    }

    return 1; // Board is full
}

int getComputerMove()
{
    // Check if the computer can win in the next move
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = 2;
                if (checkWin(2))
                {
                    return i * 3 + j + 1;
                }
                board[i][j] = 0;
            }
        }
    }

    // Check if the human can win in the next move, and block them
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = 1;
                if (checkWin(1))
                {
                    board[i][j] = 2;
                    return i * 3 + j + 1;
                }
                board[i][j] = 0;
            }
        }
    }

    // If no immediate winning or blocking move, make a random move
    int row, col;
    do
    {
        row = rand() % 3;
        col = rand() % 3;
    } while (!isValidMove(row, col));

    board[row][col] = 2;
    return row * 3 + col + 1;
}

int main()
{
    srand(time(NULL));

    int row, col;

    resetBoard();

    while (1)
    {
        drawBoard();

        // Human's turn
        printf("Your turn. Enter row and column (1-3): ");
        scanf("%d %d", &row, &col);

        row--; // Adjust to 0-based indexing
        col--;

        if (isValidMove(row, col))
        {
            makeMove(row, col, 1);
            if (checkWin(1))
            {
                drawBoard();
                printf("Congratulations! You win!\n");
                break;
            }
            else if (isMagicSquare())
            {
                drawBoard();
                printf("Congratulations! You formed a magic square!\n");
                break;
            }
            else if (isBoardFull())
            {
                drawBoard();
                printf("It's a tie!\n");
                break;
            }
        }
        else
        {
            printf("Invalid move. Try again.\n");
            continue;
        }

        // Computer's turn
        int computerMove = getComputerMove();
        printf("Computer's move: %d\n", computerMove);

        if (checkWin(2))
        {
            drawBoard();
            printf("Computer wins! Better luck next time.\n");
            break;
        }
        else if (isMagicSquare())
        {
            drawBoard();
            printf("Computer formed a magic square! You lose.\n");
            break;
        }
        else if (isBoardFull())
        {
            drawBoard();
            printf("It's a tie!\n");
            break;
        }
    }

    return 0;
}