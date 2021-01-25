
#include "time_records.h"
#include "gboard.h"

int sizex, sizey;
int main(){
    x=0; y=0;
    char c;
    choose_level();    
    
    initscr();                      //setting up ncurses
    getmaxyx(stdscr,sizey,sizex);
    start_color();    
    init_color_pairs();
    curs_set(0);
    noecho();
    refresh();
    WINDOW *field;     //displayed rooms
    WINDOW *b_left;
    
    char** array = malloc(10*sizeof(char*));
    for (int i=0; i<10; i++) {
    array[i] = malloc(i);
}
    tile** board=(tile **)malloc(MAX_HEIGHT* sizeof(tile*));
    for(int i=0; i<MAX_HEIGHT; i++){
        board[i]=(tile *)malloc(MAX_WIDTH *sizeof(tile));
    }
    time_t start_time;
    restart(board, start_time);
    //print_rows_cols();

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

    endwin();


    return 0;
}