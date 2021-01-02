#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "gboard.h"

int menu(tile board[16][16]){
    while(true){
        printf("Wybierz opcje: \n   1. Rozpocznij nowa gre\n    2. Zobacz najlepsze wyniki\n    3. Wyjdz\n");
        int mode;
        scanf("%d", &mode);
        switch (mode)
        {
        case 1: 
            board_init(board);
            lost=false;
            while(lost==false){
                print_game_state(board);
                lost=click(board);
            }
            printf("Trafiles na bombe!\n\n\n");
            break;
        case 2:
            //show_times();
            break;
        case 3: return 0;
        }
        
    }
}


int main(){
    tile board[16][16];
    menu(board);
    
    return 0;
}