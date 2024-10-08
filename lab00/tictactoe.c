#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define CELL_MAX (3 * 3 - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[3][3])
{
    int cell = 0;

    print_sep(3);
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(3);
    }
}

// aux

bool check_row (int pos,char board[3][3],char a) {
    bool res = true;
    for (int i = 0; i<2 ; i++) {
        if (board[i][pos] == board[i+1][pos] && board[i][pos] == a) {
            res = res && true;
        }
        else {
            res = false;
        }
    }
    return res;
}

bool check_col (int pos, char board[3][3],char a) {
    bool res = true;
    for (int i = 0; i<2 ; i++) {
        if (board[pos][i] == board[pos][i+1] && board[pos][i] == a) {
            res = res && true;
        }
        else {
            res = false;
        }
    }
    return res;
}

bool check_fdiag (char board[3][3],char a) {
    bool res = true;
    for (int i =0; i<2; i++) {
        if (board[i][i]== board[i+1][i+1] && board[i][i] == a) {
            res = res && true;
        }
        else { 
            res = false;
        }
    }
    return res;
}

bool check_sdiag (char board[3][3],char a) {
    bool res = true; int i = 0; int j = 2;
    while (i<3) {
        if (board[i][j] == board[j][i] && board[i][j] == a ) { 
            res = res && true;
        }
        else {
            res= false;
        }
        i++;
        j--;
    }
    return res;
}

bool check_winner (char a ,char board[3][3]) {
    bool res= false;
    if (check_fdiag(board,a)) {
        res=true;
    }
    if (check_sdiag(board,a)) {
        res=true;
    }
    for (int i = 0; i<3 ; i++) { 
        if (check_row(i,board,a)) {
            res= true;
        }
        if (check_col(i,board,a)) {
            res=true;
        }
    }
    return res;
}

//

char get_winner(char board[3][3])
{
    char winner = '-';
    if (check_winner('X',board)) {
        winner = 'X';
    }    
    if (check_winner('O',board)) {
        winner = 'O';
    } 
    //
    return winner;
}

bool has_free_cell(char board[3][3])
{
    bool free_cell=false;
    for (int i = 0; i<3; i++) {
        for (int j =0; j<3; j++) {
            if (board[i][j] == '-') { 
                free_cell = true; return free_cell ; 
            }
        }
    }
    return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[3][3] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / 3;
            int colum = cell % 3;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
