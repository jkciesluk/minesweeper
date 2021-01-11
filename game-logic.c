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

int menu(){
    while(true){
        printf("Wybierz opcje: \n   1. Rozpocznij nowa gre\n   2. Zobacz najlepsze wyniki\n   3. Wyjdz\n");
        int mode;
        scanf("%d", &mode);
        if(mode==1){
            int lvl=choose_level();
            tile board[MAX_HEIGHT][MAX_WIDTH];
            board_init(board);
            lost=false;
            time_t start_time=get_time();
            print_game_state(board);
                
            while(lost==false && left>MAX_BOMBS){
                lost=click(board);
                print_game_state(board);
                
            }
            
            if (left<=MAX_BOMBS){
                time_t end_time=get_time();
                time_t time_score=game_time(start_time, end_time);
                printf("Gratulacje, wygrales!.\nTwoj czas: ");
                print_time(time_score);
                get_records();
                int rec_pos=compare_time(time_score, lvl);
                if(rec_pos>-1){
                new_records(time_score, rec_pos, lvl);
                write_new_records();
                }
            }
            
            else{
            printf("Trafiles na bombe!\nPozostalo pol: %d\n\n\n", left-MAX_BOMBS);
            }
        }
        else if(mode==2){
            get_records();
            print_records();
        }

        else return 0;
    }
}


int main(){
    
    menu();

    return 0;
}