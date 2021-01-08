#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int MAX_HEIGHT;
int MAX_WIDTH;
int MAX_BOMBS;

int left;
bool lost;
typedef struct{
    bool clicked;
    int state;  //-1 bomb, 0-8 bombs around
    bool flag;
}tile;
int create_bombs(tile board[MAX_HEIGHT][MAX_WIDTH]);
int bombs_around(tile board[MAX_HEIGHT][MAX_WIDTH]);
int board_init(tile board[MAX_HEIGHT][MAX_WIDTH]);
void print_board(tile board[MAX_HEIGHT][MAX_WIDTH]);
void print_game_state(tile board[MAX_HEIGHT][MAX_WIDTH]);
void reveal(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j);
bool click(tile board[MAX_HEIGHT][MAX_WIDTH]);

//help functions
int amount_of_flags(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j);
int unrevealed_around(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j);
void hint_reveal(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j);
void hint_flag(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j);
int help(tile board[MAX_HEIGHT][MAX_WIDTH]);