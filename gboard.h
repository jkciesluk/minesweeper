#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
bool try;
int MAX_HEIGHT;
int MAX_WIDTH;
int MAX_BOMBS;
int x,y;
int left;
bool lost;
int bombs_left;
int sizex, sizey;


typedef struct{
    bool clicked;
    int state;  //-1 bomb, 0-8 bombs around
    bool flag;
}tile;
int create_bombs(tile board[MAX_HEIGHT][MAX_WIDTH]);
int bombs_around(tile board[MAX_HEIGHT][MAX_WIDTH]);
int board_init(tile board[MAX_HEIGHT][MAX_WIDTH]);
void reveal(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j);
bool click(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j);
int flag(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j);
int reveal_bombs(tile board[MAX_HEIGHT][MAX_WIDTH]);
void free_board(tile board[MAX_HEIGHT][MAX_WIDTH]);
//help functions
int amount_of_flags(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j);
int unrevealed_around(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j);
void hint_reveal(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j);
void hint_flag(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j);
int help(tile board[MAX_HEIGHT][MAX_WIDTH]);
bool guess_move(tile board[MAX_HEIGHT][MAX_WIDTH]);

//ncurses ui

WINDOW *create_window(int height, int width, int posy, int posx, bool border);
void print_ncurses_board(WINDOW *win, tile board[MAX_HEIGHT][MAX_WIDTH]);
void print_ham(WINDOW *win);
void print_help(WINDOW *win);
void init_color_pairs();
void print_rows_cols();
void print_bombs_left(WINDOW* win);