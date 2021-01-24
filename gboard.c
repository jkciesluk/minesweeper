#include "gboard.h"

int create_bombs(tile board[MAX_HEIGHT][MAX_WIDTH]){            //randomly generates bombs on board
    srand(time(NULL));
    int row, column;
    for(int i=0; i<MAX_BOMBS; i++){
        row=rand()%MAX_HEIGHT;
        column=rand()%MAX_WIDTH;
        while (board[row][column].state==-1)
        {
            row=rand()%MAX_HEIGHT;
            column=rand()%MAX_WIDTH;
        }
        board[row][column].state=-1;
        //printf("%d %d \n", row, column);
    }
    return 1;
}

int bombs_around(tile board[MAX_HEIGHT][MAX_WIDTH]){                //give each tile value equal to amount of surrounding bombs
    
    for(int i=0; i<MAX_HEIGHT; i++){
        for(int j=0; j<MAX_WIDTH; j++){
            if (board[i][j].state==-1)
            {
                if(j<MAX_WIDTH-1) if(board[i][j+1].state!=-1) board[i][j+1].state++;                //dol
                if(i<MAX_HEIGHT-1 && j<MAX_WIDTH-1) if(board[i+1][j+1].state!=-1) board[i+1][j+1].state++;                //dol prawo
                if(i<MAX_HEIGHT-1) if(board[i+1][j].state!=-1) board[i+1][j].state++;                //prawo
                if(i<MAX_HEIGHT-1 && j>0) if(board[i+1][j-1].state!=-1) board[i+1][j-1].state++;                //gora prawo
                if(j>0) if(board[i][j-1].state!=-1) board[i][j-1].state++;                //gora
                if(i>0 && j>0) if(board[i-1][j-1].state!=-1) board[i-1][j-1].state++;                //gora lewo
                if(i>0) if(board[i-1][j].state!=-1) board[i-1][j].state++;                //lewo
                if(i>0 && j<MAX_WIDTH-1) if(board[i-1][j+1].state!=-1) board[i-1][j+1].state++;                //dol lewo
            }
        }
    }
    return 1;
}

int board_init(tile board[MAX_HEIGHT][MAX_WIDTH]){          //creates new game board
    left=MAX_HEIGHT*MAX_WIDTH;
    for(int i=0; i<MAX_HEIGHT; i++){
        for(int j=0; j<MAX_WIDTH; j++){
            board[i][j].state=0;
            board[i][j].clicked=false;
            board[i][j].flag=false;
        }
    }    
     
    create_bombs(board);
    bombs_around(board);
    return 1;
}

void reveal(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j){                  //if tile ==0, reveal surrounding tiles recursively
                
                if(j<MAX_WIDTH-1 && board[i][j+1].clicked==false) {board[i][j+1].clicked=true;              left--;      if(board[i][j+1].state==0) reveal(board, i, j+1);}
                if(i<MAX_HEIGHT-1 && j<MAX_WIDTH-1  && board[i+1][j+1].clicked==false){ board[i+1][j+1].clicked=true; left--;      if(board[i+1][j+1].state==0) reveal(board, i+1, j+1);}
                if(i<MAX_HEIGHT-1  && board[i+1][j].clicked==false){ board[i+1][j].clicked=true;             left--;      if(board[i+1][j].state==0) reveal(board, i+1, j);}
                if(i<MAX_HEIGHT-1 && j>0  && board[i+1][j-1].clicked==false){ board[i+1][j-1].clicked=true;  left--;      if(board[i+1][j-1].state==0) reveal(board, i+1, j-1);}
                if(j>0  && board[i][j-1].clicked==false){ board[i][j-1].clicked=true;              left--;      if(board[i][j-1].state==0 ) reveal(board, i, j-1);}
                if(i>0 && j>0  && board[i-1][j-1].clicked==false){ board[i-1][j-1].clicked=true;   left--;      if(board[i-1][j-1].state==0) reveal(board, i-1, j-1);}
                if(i>0  && board[i-1][j].clicked==false){ board[i-1][j].clicked=true;              left--;      if(board[i-1][j].state==0) reveal(board, i-1, j);}
                if(i>0 && j<MAX_WIDTH-1  && board[i-1][j+1].clicked==false){ board[i-1][j+1].clicked=true;  left--;      if(board[i-1][j+1].state==0) reveal(board, i-1, j+1);}
}

int flag(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j){                              //flag selected tile
    if(board[i][j].flag==false){ board[i][j].flag=true; board[i][j].clicked=true;}
    else {board[i][j].flag=false; board[i][j].clicked=false;}
    return 1;        
}


bool click(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j){                //reveal selected tile
        board[i][j].flag=false;
        board[i][j].clicked=true;
        if(board[i][j].state==-1) {
            //printf("Bomba\n"); 
            lost=true;
            return true;

        } 
        left--;
        if(board[i][j].state==0) reveal(board, i, j);

    return false;
}



//Here I go with hint/help part
int amount_of_flags(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j){               //amount of flags around the tile
    int aof=0;
                if(j<MAX_WIDTH-1) if(board[i][j+1].flag) aof++;                 //dol
                if(i<MAX_HEIGHT-1 && j<MAX_WIDTH-1) if(board[i+1][j+1].flag) aof++;                //dol prawo
                if(i<MAX_HEIGHT-1) if(board[i+1][j].flag)  aof++;               //prawo
                if(i<MAX_HEIGHT-1 && j>0) if(board[i+1][j-1].flag) aof++;                //gora prawo
                if(j>0) if(board[i][j-1].flag)  aof++;               //gora
                if(i>0 && j>0) if(board[i-1][j-1].flag) aof++;                //gora lewo
                if(i>0) if(board[i-1][j].flag) aof++;                //lewo
                if(i>0 && j<MAX_WIDTH-1) if(board[i-1][j+1].flag) aof++;                //dol lewo
    return aof;
}

int unrevealed_around(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j){             //amount of unrevealed tiles around
        int unr=0;
                if(j<MAX_WIDTH-1) if(!board[i][j+1].clicked) unr++;                 //dol
                if(i<MAX_HEIGHT-1 && j<MAX_WIDTH-1) if(!board[i+1][j+1].clicked) unr++;                //dol prawo
                if(i<MAX_HEIGHT-1) if(!board[i+1][j].clicked)  unr++;               //prawo
                if(i<MAX_HEIGHT-1 && j>0) if(!board[i+1][j-1].clicked) unr++;                //gora prawo
                if(j>0) if(!board[i][j-1].clicked)  unr++;               //gora
                if(i>0 && j>0) if(!board[i-1][j-1].clicked) unr++;                //gora lewo
                if(i>0) if(!board[i-1][j].clicked) unr++;                //lewo
                if(i>0 && j<MAX_WIDTH-1) if(!board[i-1][j+1].clicked) unr++;                //dol lewo
           return unr;
}

void hint_reveal(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j){          //reveal() for help function
                
                if(j<MAX_WIDTH-1 && board[i][j+1].clicked==false && board[i][j+1].flag==false) {board[i][j+1].clicked=true;                 left--;             if(board[i][j+1].state==0) reveal(board, i, j+1);}
                if(i<MAX_HEIGHT-1 && j<MAX_WIDTH-1  && board[i+1][j+1].clicked==false && board[i+1][j+1].flag==false){ board[i+1][j+1].clicked=true;  left--;   if(board[i+1][j+1].state==0) reveal(board, i+1, j+1);}
                if(i<MAX_HEIGHT-1  && board[i+1][j].clicked==false && board[i+1][j].flag==false){ board[i+1][j].clicked=true;                left--;            if(board[i+1][j].state==0) reveal(board, i+1, j);}
                if(i<MAX_HEIGHT-1 && j>0  && board[i+1][j-1].clicked==false && board[i+1][j-1].flag==false){ board[i+1][j-1].clicked=true;   left--;            if(board[i+1][j-1].state==0) reveal(board, i+1, j-1);}
                if(j>0  && board[i][j-1].clicked==false && board[i][j-1].flag==false){ board[i][j-1].clicked=true;                 left--;                      if(board[i][j-1].state==0 ) reveal(board, i, j-1);}
                if(i>0 && j>0  && board[i-1][j-1].clicked==false && board[i-1][j-1].flag==false){ board[i-1][j-1].clicked=true;    left--;                      if(board[i-1][j-1].state==0) reveal(board, i-1, j-1);}
                if(i>0  && board[i-1][j].clicked==false && board[i-1][j].flag==false){ board[i-1][j].clicked=true;                 left--;                      if(board[i-1][j].state==0) reveal(board, i-1, j);}
                if(i>0 && j<MAX_WIDTH-1  && board[i-1][j+1].clicked==false && board[i-1][j+1].flag==false){ board[i-1][j+1].clicked=true;   left--;             if(board[i-1][j+1].state==0) reveal(board, i-1, j+1);}
}


void hint_flag(tile board[MAX_HEIGHT][MAX_WIDTH], int i, int j){            //flag() for help function

        if(j<MAX_WIDTH-1) if(!board[i][j+1].clicked) {board[i][j+1].flag=true; board[i][j+1].clicked=true;}                 //dol
        if(i<MAX_HEIGHT-1 && j<MAX_WIDTH-1) if(!board[i+1][j+1].clicked) {board[i+1][j+1].flag=true; board[i+1][j+1].clicked=true;}                //dol prawo
        if(i<MAX_HEIGHT-1) if(!board[i+1][j].clicked)  {board[i+1][j].flag=true; board[i+1][j].clicked=true;}                //prawo
        if(i<MAX_HEIGHT-1 && j>0) if(!board[i+1][j-1].clicked) {board[i+1][j-1].flag=true; board[i+1][j-1].clicked=true;}                //gora prawo
        if(j>0) if(!board[i][j-1].clicked)  {board[i][j-1].flag=true; board[i][j-1].clicked=true;}               //gora
        if(i>0 && j>0) if(!board[i-1][j-1].clicked) {board[i-1][j-1].flag=true; board[i-1][j-1].clicked=true;}                //gora lewo
        if(i>0) if(!board[i-1][j].clicked) {board[i-1][j].flag=true; board[i-1][j].clicked=true;}                //lewo
        if(i>0 && j<MAX_WIDTH-1) if(!board[i-1][j+1].clicked) {board[i-1][j+1].flag=true; board[i-1][j+1].clicked=true;}                //dol lewo
}

int help(tile board[MAX_HEIGHT][MAX_WIDTH]){                    //helps by revealing safe tiles or putting flags on bombs
    int aof=0; //amount of flags
    int unr=0; //unrevealed tiles around
    for(int i=0; i<MAX_HEIGHT; i++){
        for(int j=0; j<MAX_WIDTH; j++){
            if(board[i][j].clicked==true && board[i][j].state>0 && board[i][j].flag==false){      //checking if amount of tiles with flags around is equal to amount of bombs
                aof=amount_of_flags(board, i, j);
                unr=unrevealed_around(board, i, j);
                if(aof==board[i][j].state && unr>0){
                        hint_reveal(board, i, j);
                        return 1;
                }
                else if(aof>board[i][j].state){
                    return 1;
                }

                else{                   //case if amount of flags < tile value
                    if(unr==board[i][j].state-aof && unr>0){
                        hint_flag(board, i, j);
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

bool guess_move(tile board[MAX_HEIGHT][MAX_WIDTH]){
    int s=0, i=0, j=0;
    while((board[i][j].clicked==true || board[i][j].flag==true)){
        if(s%2==0){ if(i<MAX_HEIGHT-1) i++; else if(j<MAX_WIDTH-1) j++;}
        else { if(j<MAX_WIDTH-1) j++; else if(i<MAX_HEIGHT-1) i++;}
        s++;
        if(s>MAX_HEIGHT+MAX_WIDTH) return false;
    }
    click(board, i,j);
    return true;
}