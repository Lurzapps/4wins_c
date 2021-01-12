#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

#define NL "\n\r"

void printField();

void printHeader();

int checkWin(int, int, char);

enum FieldValues {
    EMPTY = ' ', PL1 = 'x', PL2 = 'o'
};

const int ROWS = 6, COLUMNS = 7;

char field[6][7];
boolean player1 = true;

int main() {
    //init variables
    int r, c, playerColumn, playerRow;
    int result = 0;
    char symbol;
    char *turn;

    //init empty columns and rows
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLUMNS; c++)
            field[r][c] = EMPTY;
    }

    do {
        //print
        printField();
        //determine current symbol
        symbol = player1 ? PL1 : PL2;
        //input column
        turn = player1 ? "Player 1" : "Player 2";

        printf(NL "%s ( %c ) - please enter column:", turn, symbol);
        scanf("%i", &playerColumn);
        fflush(stdin);

        if ((playerColumn > 0) && (playerColumn <= COLUMNS)) {
            //correct the index
            playerColumn--;
            // determine to which row index the symbol drops
            if (field[0][playerColumn] == EMPTY) {
                for (r = (ROWS - 1); r >= 0; r--) {
                    if (field[r][playerColumn] == EMPTY) {
                        playerRow = r;
                        field[r][playerColumn] = symbol;
                        break;
                    }
                }

                // check for win
                result = checkWin(playerRow, playerColumn, symbol);
                //switch player
                player1 = !player1;
            } else {
                printf(NL "Your selected row is full, please choose another one!");
            }
        } else {
            printf(NL "Invalid input");
        }
    } while (result == 0);

    printField();

    if (result == 2)
        printf(NL NL "%s ( %c ) won!", turn, symbol);
    else
        printf(NL NL "Tie!");

    return 0;
}

void printHeader() {
    printf(NL);
    for (int i = 0; i < 39; i++)
        printf("-");
}

void printField() {
    //leave cleaning the screen out, misleads ide console
    //system("cls");
    //print a header
    printHeader();
    //print the field as matrix
    int r, c;
    for (r = 0; r < ROWS; r++) {
        printf(NL);

        for (c = 0; c < COLUMNS; c++) {
            printf(" | %c ", field[r][c]);

            if (c == COLUMNS - 1)
                printf(" | ");
        }
    }
    //print header again
    printHeader();
    //print column names
    printf(NL "  ");
    for (int i = 0; i < COLUMNS; i++)
        printf("  %d  ", i + 1);
}

int checkWin(int plR, int plC, char symbol) {
    int r, c;
    int C_MAX = COLUMNS - 3, R_MAX = ROWS - 3;

    //check for tie
    int sumOfSetFields = 0;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLUMNS; c++) {
            if (field[r][c] != EMPTY)
                sumOfSetFields++;
        }
    }

    if (sumOfSetFields == (ROWS * COLUMNS))
        return 1;

    //check altered column for win
    for (c = 0; c < C_MAX; c++) {
        if ((field[plR][c] == symbol) && (field[plR][c + 1] == symbol) && (field[plR][c + 2] == symbol) &&
            (field[plR][c + 3] == symbol))
            return 2;
    }

    //check altered row for win
    for (r = 0; r < R_MAX; r++) {
        if ((field[r][plC] == symbol) && (field[r + 1][plC] == symbol) && (field[r + 2][plC] == symbol) &&
            (field[r + 3][plC] == symbol))
            return 2;
    }

    //for diagonals check the whole field
    //top left to bottom right
    for (c = 0; c < C_MAX; c++) {
        for (r = 0; r < R_MAX; r++) {
            if ((field[r][c] == symbol) && (field[r + 1][c + 1] == symbol) && (field[r + 2][c + 2] == symbol) &&
                (field[r + 3][c + 3] == symbol))
                return 2;
        }
    }

    // top mid to bottom left
    for (c = 3; c < COLUMNS; c++) {
        for (r = 0; r < R_MAX; r++) {
            if ((field[r][c] == symbol) && (field[r + 1][c - 1] == symbol) && (field[r + 2][c - 2] == symbol) &&
                (field[r + 3][c - 3] == symbol))
                return 2;
        }
    }

    return 0;
}