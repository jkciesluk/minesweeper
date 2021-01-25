
#include "time_records.h"
#include "gboard.h"

int sizex, sizey;
int main(){
    x=0; y=0;
    char c;
    
    initscr();                      //setting up ncurses
    start_color();    
    init_color_pairs();
    curs_set(0);
    noecho();
    refresh();
    time_t start_time;
    while (1)
    {    
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
    refresh();
    getch();

    endwin();


    return 0;
}