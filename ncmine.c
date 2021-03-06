
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
    
    int option=0;
    char c=0;
    while (1)
    {
    getmaxyx(stdscr,sizey,sizex);
    attron(COLOR_PAIR(1));
    attron(A_BOLD);
    mvprintw(2, sizex/2-12, "M I N E S W E E P E R");
    attroff(COLOR_PAIR(1));                                                 //main menu
    attroff(A_BOLD);
    
    mvprintw(sizey/2+8, sizex/2-10, "Use W, S to navigate");
    mvprintw(sizey/2+9, sizex/2-10, "Press ENTER to choose option");

    while(c!=10 && c!=13){
        print_menu(option);
        c=getch();
        if(c=='w') {option--; if(option<0) option=2;}
        else if(c=='s'){option++; if(option>3) option=0;}   
    }
    if (option==0)
    {
        clear();
            
        int lvl=choose_level();                                         //creating game board
        clear();
        tile** board=(tile **)malloc(MAX_HEIGHT* sizeof(tile*));
        for(int i=0; i<MAX_HEIGHT; i++){
            board[i]=(tile *)malloc(MAX_WIDTH *sizeof(tile));
        }
        WINDOW *field;     //displayed rooms
        WINDOW *b_left;
        restart(board);
        
        refresh();
        getmaxyx(stdscr,sizey,sizex);
        sizex=sizex/2-MAX_WIDTH;                        //printing game
        sizey=(sizey-MAX_HEIGHT)/2;
        field=create_window(MAX_HEIGHT+2, MAX_WIDTH*2+3, sizey, sizex, TRUE);
        move(sizey+1,sizex+1);
        b_left=create_window(3, 9, sizey-3, sizex, TRUE);
        x=0; y=0;
        print_ncurses_board(field, board);
        print_bombs_left(b_left);
        
        while(lost==false && left>MAX_BOMBS){           //actual game
            c=getch();                                  
            action(board, c, start_time);
            print_bombs_left(b_left);       
            print_ncurses_board(field, board);    
            refresh();
        }
        reveal_bombs(board);
        print_ncurses_board(field, board);    
        if(left<=MAX_BOMBS){                                    //if won, compare score
            time_t end_time=get_time();
            time_t time_score=game_time(start_time, end_time);
            mvprintw(sizey-2, sizex+10, "You won! Your time: %02ld:%02ld:%02ld", time_score/3600, time_score%3600/60, time_score%60);
            get_records();
            if(compare_time(time_score, lvl)>-1){
                new_records(time_score,compare_time(time_score, lvl) ,lvl);
                write_new_records();
            }
        }
        else            //if lost
        {
            mvprintw(sizey-2, sizex+10, "You lost! Bombs left: %02d", bombs_left); 
        }
        
        
        refresh();
        getch();
        clear();
        free_board(board);
        delwin(field);
        delwin(b_left);
        refresh();
        }
    else if(option==1)
    {
        c=0;
        option=0;
        get_records();
        print_ncurses_records();
    }
    else if(option==2){
        c=0;
        option=0;
        clear();
        how_to_play();
        refresh();
        getch();
        clear();
    }
    else{   
        endwin();
        return 0;
    }
    
    }   

    return 0;
}