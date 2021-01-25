#include "gboard.h"


WINDOW *create_window(int height, int width, int posy, int posx, bool border){
    WINDOW *tmp;
    tmp=newwin(height, width, posy, posx);
    if(border){
        box(tmp, 0 , 0);
    }
    wrefresh(tmp);
    return tmp;
}

void print_ncurses_board(WINDOW *win, tile** board){
    for (int i = 0; i < MAX_HEIGHT; i++)
    {
        for(int j=0; j<MAX_WIDTH; j++){
            if(board[i][j].clicked==false) mvwprintw(win, 1+i, 1+j*2, " x ");   
            else if(board[i][j].flag) {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 1+i, 1+j*2, " F ");
                wattroff(win, COLOR_PAIR(2));
            }
            else{
            switch (board[i][j].state)
            {
            case -1:
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 1+i, 1+j*2, " B ", board[i][j].state);
                wattroff(win, COLOR_PAIR(2));
                break;
            case 4:
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 1+i, 1+j*2, " %d ", board[i][j].state);
                wattroff(win, COLOR_PAIR(3));
                break;
            case 3:
                wattron(win, COLOR_PAIR(4));
                mvwprintw(win, 1+i, 1+j*2, " %d ", board[i][j].state);
                wattroff(win, COLOR_PAIR(4));
                break;
            case 2:
                wattron(win, COLOR_PAIR(1));
                mvwprintw(win, 1+i, 1+j*2, " %d ", board[i][j].state);
                wattroff(win, COLOR_PAIR(1));
                break;
            case 1:
                wattron(win, COLOR_PAIR(5));
                mvwprintw(win, 1+i, 1+j*2, " %d ", board[i][j].state);
                wattroff(win, COLOR_PAIR(5));
                break;
                
            default: 
                mvwprintw(win, 1+i, 1+j*2, " %d ", board[i][j].state);
                break;
            }
            }
        }
    }
    mvwprintw(win, 1+y, 1+x*2, "<");
    mvwprintw(win, 1+y, 3+x*2, ">");
    wrefresh(win);
}

void print_bombs_left(WINDOW* win){
    if(bombs_left!=MAX_BOMBS)mvwprintw(win, 1, 1, "%2.d/%2.d", MAX_BOMBS-bombs_left, MAX_BOMBS);
    else{mvwprintw(win, 1, 1, " 0/%2.d", MAX_BOMBS);}
    wrefresh(win);
}


void init_color_pairs(){
    init_pair(1, COLOR_GREEN, 0);
    init_pair(2, COLOR_RED, 0);
    init_pair(3, COLOR_YELLOW, 0);
    init_pair(4, COLOR_CYAN, 0);
    init_pair(5, COLOR_BLUE, 0);
    init_pair(6, COLOR_MAGENTA, 0);
}

void print_rows_cols(){
    for(int i=0; i<MAX_WIDTH; i++){
        mvprintw(4,7+2*i, "%d", i%10);
    }
    for(int i=0; i<MAX_HEIGHT; i++){
        mvprintw(6+i, 3, "%d", i%10);
    }
}
