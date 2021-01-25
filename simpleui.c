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
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
}

void print_rows_cols(){
    for(int i=0; i<MAX_WIDTH; i++){
        mvprintw(4,7+2*i, "%d", i%10);
    }
    for(int i=0; i<MAX_HEIGHT; i++){
        mvprintw(6+i, 3, "%d", i%10);
    }
}


int choose_level(){
    getmaxyx(stdscr,sizey,sizex);
    mvprintw(sizey/2+8, sizex/2-10, "Use W, S to navigate");
    mvprintw(sizey/2+9, sizex/2-10, "Press ENTER to choose option");
    mvprintw(sizey/2-3, sizex/2-8, "Choose level:");
    char c=0;
    int option=0;
    while(c!=10 && c!=13){
    if(option==0){
        attron(COLOR_PAIR(7));
        mvprintw(sizey/2-2, sizex/2-6, " Easy  ");
        attroff(COLOR_PAIR(7));
        mvprintw(sizey/2-1, sizex/2-6, " Medium ");
        mvprintw(sizey/2, sizex/2-6, " Hard  ");
    }
    else if(option==1){
        mvprintw(sizey/2-2, sizex/2-6, " Easy  ");
        attron(COLOR_PAIR(7));
        mvprintw(sizey/2-1, sizex/2-6, " Medium ");
        attroff(COLOR_PAIR(7));
        mvprintw(sizey/2, sizex/2-6, " Hard  ");
    }
    else if(option==2){
        mvprintw(sizey/2-2, sizex/2-6, " Easy  ");
        mvprintw(sizey/2-1, sizex/2-6, " Medium ");
        attron(COLOR_PAIR(7));
        mvprintw(sizey/2, sizex/2-6, " Hard  ");
        attroff(COLOR_PAIR(7));
    }
    c=getch();
    if(c=='w') {option--; if(option<0) option=2;}
    else if(c=='s'){option++; if(option>2) option=0;}   
    }
    if(option==0){
        MAX_HEIGHT=9;
        MAX_WIDTH=9;
        MAX_BOMBS=10;
        return 1;
    }
    else if(option==2){
        MAX_BOMBS=99;
        MAX_HEIGHT=16;
        MAX_WIDTH=30;
        return 3;
    }
    else
    {   
        MAX_BOMBS=40;
        MAX_HEIGHT=16;
        MAX_WIDTH=16;
        return 2;
    }
}

void how_to_play(){
    getmaxyx(stdscr,sizey,sizex);
    mvprintw(sizey/2, sizex/2-6, "Tutaj beda informacje o grze");
    refresh();
}