#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
int left;
bool lost;
typedef struct{
    bool clicked;
    int state;  //-1 bomb, 0-8 bombs around
    bool flag;
}tile;
int create_bombs(tile board[16][16]);
int bombs_around(tile board[16][16]);
int board_init(tile board[16][16]);
void print_board(tile board[16][16]);
void print_game_state(tile board[16][16]);
void reveal(tile board[16][16], int i, int j);
bool click(tile board[16][16]);

//help functions
int amount_of_flags(tile board[16][16], int i, int j);
int unrevealed_around(tile board[16][16], int i, int j);
void hint_reveal(tile board[16][16], int i, int j);
void hint_flag(tile board[16][16], int i, int j);
int help(tile board[16][16]);