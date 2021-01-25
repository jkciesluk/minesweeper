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
int create_bombs(tile** board);
int bombs_around(tile** board);
int board_init(tile** board);
void reveal(tile** board, int i, int j);
bool click(tile** board, int i, int j);
int flag(tile** board, int i, int j);
int reveal_bombs(tile** board);
void free_board(tile** board);
//help functions
int amount_of_flags(tile** board, int i, int j);
int unrevealed_around(tile** board, int i, int j);
void hint_reveal(tile** board, int i, int j);
void hint_flag(tile** board, int i, int j);
int help(tile** board);
bool guess_move(tile** board);

//ncurses ui

WINDOW *create_window(int height, int width, int posy, int posx, bool border);
void print_ncurses_board(WINDOW *win, tile** board);
void print_ham(WINDOW *win);
void print_help(WINDOW *win);
void init_color_pairs();
void print_rows_cols();
void print_bombs_left(WINDOW* win);