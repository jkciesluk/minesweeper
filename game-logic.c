#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool lost;

typedef struct{
    bool clicked;
    int state;  //-1 bomb, 0-8 bombs around
    bool flag;
}tile;

int create_bombs(tile board[16][16]){
    srand(time(NULL));
    int row, column;
    for(int i=0; i<40; i++){
        row=rand()%16;
        column=rand()%16;
        while (board[row][column].state==-1)
        {
            row=rand()%16;
            column=rand()%16;
        }
        board[row][column].state=-1;
        printf("%d %d \n", row, column);
    }
    return 1;
}

int bombs_around(tile board[16][16]){
    
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            if (board[i][j].state==-1)
            {
                if(j<15) if(board[i][j+1].state!=-1) board[i][j+1].state++;                //dol
                if(i<15 && j<15) if(board[i+1][j+1].state!=-1) board[i+1][j+1].state++;                //dol prawo
                if(i<15) if(board[i+1][j].state!=-1) board[i+1][j].state++;                //prawo
                if(i<15 && j>0) if(board[i+1][j-1].state!=-1) board[i+1][j-1].state++;                //gora prawo
                if(j>0) if(board[i][j-1].state!=-1) board[i][j-1].state++;                //gora
                if(i>0 && j>0) if(board[i-1][j-1].state!=-1) board[i-1][j-1].state++;                //gora lewo
                if(i>0) if(board[i-1][j].state!=-1) board[i-1][j].state++;                //lewo
                if(i>0 && j<15) if(board[i-1][j+1].state!=-1) board[i-1][j+1].state++;                //dol lewo
            }
        }
    }
    return 1;
}

int board_init(tile board[16][16]){
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            board[i][j].state=0;
            board[i][j].clicked=false;
            board[i][j].flag=false;
        }
    }    
     
    create_bombs(board);
    bombs_around(board);
    return 1;
}

void print_board(tile board[16][16]){
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            if(board[i][j].state!=-1) printf(" %d", board[i][j].state);
            else    printf("%d", board[i][j].state);
        }
        printf("\n");
    }
            
}

void print_game_state(tile board[16][16]){
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            //if(board[i][j].state==-1) printf("%d", board[i][j].state);
            if(board[i][j].clicked==false) printf(" x");
            else if(board[i][j].state!=-1) printf(" %d", board[i][j].state);
            else    printf("%d", board[i][j].state);
        }
        printf("\n");
    }
    
}

void reveal(tile board[16][16], int i, int j){
                if(j<15) {
                    board[i][j+1].clicked=true;               
                    if(board[i][j+1].state==0) 
                        reveal(board, i, j+1);
                }
                if(i<15 && j<15  && board[i+1][j+1].clicked==false){ board[i+1][j+1].clicked=true;        if(board[i+1][j+1].state==0) reveal(board, i+1, j+1);}
                if(i<15  && board[i+1][j].clicked==false){ board[i+1][j].clicked=true;                  if(board[i+1][j].state==0) reveal(board, i+1, j);}
                if(i<15 && j>0  && board[i+1][j-1].clicked==false){ board[i+1][j-1].clicked=true;         if(board[i+1][j-1].state==0) reveal(board, i+1, j-1);}
                if(j>0  && board[i][j-1].clicked==false){ board[i][j-1].clicked=true;                   if(board[i][j-1].state==0 ) reveal(board, i, j-1);}
                if(i>0 && j>0  && board[i-1][j-1].clicked==false){ board[i-1][j-1].clicked=true;          if(board[i-1][j-1].state==0) reveal(board, i-1, j-1);}
                if(i>0  && board[i-1][j].clicked==false){ board[i-1][j].clicked=true;                   if(board[i-1][j].state==0) reveal(board, i-1, j);}
                if(i>0 && j<15  && board[i-1][j+1].clicked==false){ board[i-1][j+1].clicked=true;         if(board[i-1][j+1].state==0) reveal(board, i-1, j+1);}
}

bool click(tile board[16][16]){
    int i,j;
    scanf("%d %d", &i, &j);       //y poziom, x pion
    while(board[i][j].clicked==true){
        printf("To pole juz jest odkryte, wybierz inne!\n");
        scanf("%d %d", &i, &j);       //y poziom, x pion    
    }
    board[i][j].clicked=true;
    if(board[i][j].state==-1) {printf("Bomba\n"); return true;} 
    if(board[i][j].state==0){
       reveal(board, i, j);
    }
    return false;
}




int main(){
    tile board[16][16];
    board_init(board);
    //print_game_state(board);
    lost=false;
    while(lost==false){
        print_game_state(board);
        lost=click(board);
        
    }
    printf("Trafiles na bombe!\n");
    return 0;
}