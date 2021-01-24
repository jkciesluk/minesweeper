
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


int main(){
    x=0; y=0;
    choose_level();    
    initscr();
    start_color();    
    init_color_pairs();
    curs_set(0);
    noecho();
    refresh();
    tile board[MAX_HEIGHT][MAX_WIDTH];
    board_init(board);
    WINDOW *field;     //displayed rooms
    WINDOW *help;
    for(int i=0; i<MAX_WIDTH; i++){
        mvprintw(4,7+2*i, "%d", i%10);
    }
    for(int i=0; i<MAX_HEIGHT; i++){
        mvprintw(6+i, 3, "%d", i%10);
    }
    field=create_window(MAX_HEIGHT+2, MAX_WIDTH*2+3, 5, 5, TRUE);
    move(6,6);
    char c;
    print_ncurses_board(field, board);

    while(lost==false && left>MAX_BOMBS){
        c=getch();
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

        default:
            break;
        }
       print_ncurses_board(field, board);    
    refresh();

    }
    
    getch();
    endwin();


    return 0;
}