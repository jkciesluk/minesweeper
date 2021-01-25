
#include "time_records.h"
#include "gboard.h"
int choose_level(){
    printf("Wybierz poziom trudnosci: \n1. Latwy\n2. Sredni \n3. Trudny\n");
    int l;
    scanf("%d", &l);
    if(l==1){
        MAX_HEIGHT=9;
        MAX_WIDTH=9;
        MAX_BOMBS=10;
        return 1;
    }
    else if(l==3){
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


int restart(tile** board, time_t start_time){
            start_time=get_time();
            board_init(board);
            lost=false;
            bombs_left=MAX_BOMBS;    
}

bool action(tile** board, char c, time_t start_time){
    switch (c)
        {
        case 'w':
            if(y>0)y--;
            break;
        case 's':
            if(y<MAX_HEIGHT-1)y++;
            break;
        case 'a':
            if(x>0)x--;
            break;
        case 'd':
            if(x<MAX_WIDTH-1)x++;
            break;
        case ' ':
            click(board, y, x);
            break;
        case 'f':
            flag(board, y, x);
            break;
        case '1':
            help(board);
            break;
        case '2':
            while(help(board));
            break;
        case '3':
            try=true;
            while (lost==false && left>MAX_BOMBS && try)
            {
                while(help(board));
                if(left>MAX_BOMBS) try=guess_move(board);
            }
            break;
        case 'r':
            restart(board, start_time);
            break;
        default:
            break;
        }
    return lost;
}

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