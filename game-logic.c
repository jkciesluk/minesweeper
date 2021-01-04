#include "time_records.h"
#include "gboard.h"

int menu(tile board[16][16]){
    while(true){
        printf("Wybierz opcje: \n   1. Rozpocznij nowa gre\n   2. Zobacz najlepsze wyniki\n   3. Wyjdz\n");
        int mode;
        scanf("%d", &mode);
        switch (mode)
        {
        case 1: 
            board_init(board);
            lost=false;
            time_t start_time=get_time();
            while(lost==false && left>40){
                print_game_state(board);
                lost=click(board);
            }
            
            if (left<=40){
                time_t end_time=get_time();
                time_t time_score=game_time(start_time, end_time);
                printf("Gratulacje, wygrales!.\nTwoj czas: ");
                print_time(time_score);
            }
            
            else{
            printf("Trafiles na bombe!\nPozostalo pol: %d\n\n\n", left-40);
            
            }
            
            
            break;
        case 2:
            //show_times();
            get_records();
            break;
        case 3: return 0;
        }
        
    }
}


int main(){
    tile board[16][16];
    time_t t=247;
    print_time(t);
    menu(board);
    

    return 0;
}