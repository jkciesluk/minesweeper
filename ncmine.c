
#include "time_records.h"
#include "gboard.h"

int sizex, sizey;
int main(){
    x=0; y=0;
    
    initscr();                      //setting up ncurses
    start_color();    
    init_color_pairs();
    curs_set(0);
    noecho();
    refresh();
    time_t start_time;
    int option=0;
    char c=0;
    while (1)
    {
    getmaxyx(stdscr,sizey,sizex);
    mvprintw(sizey/2+8, sizex/2-10, "Use W, S to navigate");
    mvprintw(sizey/2+9, sizex/2-10, "Press ENTER to choose option");
    while(c!=10 && c!=13){
    if(option==0){
        attron(COLOR_PAIR(7));
        mvprintw(sizey/2-2, sizex/2-6, " New game  ");
        attroff(COLOR_PAIR(7));
        mvprintw(sizey/2-1, sizex/2-6, " Records   ");
        mvprintw(sizey/2, sizex/2-6, " Exit game ");
    }
    else if(option==1){
        mvprintw(sizey/2-2, sizex/2-6, " New game  ");
        attron(COLOR_PAIR(7));
        mvprintw(sizey/2-1, sizex/2-6, " Records   ");
        attroff(COLOR_PAIR(7));
        mvprintw(sizey/2, sizex/2-6, " Exit game ");
    }
    else if(option==2){
        mvprintw(sizey/2-2, sizex/2-6, " New game  ");
        mvprintw(sizey/2-1, sizex/2-6, " Records   ");
        attron(COLOR_PAIR(7));
        mvprintw(sizey/2, sizex/2-6, " Exit game ");
        attroff(COLOR_PAIR(7));
    }
    c=getch();
    if(c=='w') {option--; if(option<0) option=2;}
    else if(c=='s'){option++; if(option>2) option=0;}   
    }
    if (option==0)
    {
        clear();
        
        choose_level();
        clear();
        tile** board=(tile **)malloc(MAX_HEIGHT* sizeof(tile*));
        for(int i=0; i<MAX_HEIGHT; i++){
            board[i]=(tile *)malloc(MAX_WIDTH *sizeof(tile));
        }
        WINDOW *field;     //displayed rooms
        WINDOW *b_left;
    
        restart(board, start_time);
        //print_rows_cols();
        refresh();
        getmaxyx(stdscr,sizey,sizex);
        sizex=sizex/2-MAX_WIDTH;                        //printing game
        sizey=(sizey-MAX_HEIGHT)/2;
        field=create_window(MAX_HEIGHT+2, MAX_WIDTH*2+3, sizey, sizex, TRUE);
        move(sizey+1,sizex+1);
        b_left=create_window(3, 8, sizey-3, sizex, TRUE);
    
        print_ncurses_board(field, board);
        print_bombs_left(b_left);
    
        while(lost==false && left>MAX_BOMBS){
            c=getch();
            action(board, c, start_time);
            print_bombs_left(b_left);       
            print_ncurses_board(field, board);    
            refresh();
        }
        reveal_bombs(board);
        print_ncurses_board(field, board);    
        refresh();
        getch();
        clear();
        for(int i=0; i<MAX_HEIGHT; i++){
            free(board[i]);
        }
        free(board);
        delwin(field);
        delwin(b_left);
        refresh();
        }
    else if(option==1)
    {
        //print_ncurses_records();
    }
    else
    {   
        endwin();
        return 0;
    }
    
    }   
    refresh();
    getch();

    endwin();


    return 0;
}