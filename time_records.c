#include "time_records.h"

time_t get_time(){
    return time(NULL);
}

time_t game_time(time_t t1, time_t t2){
    return t2-t1;
}


int conv(const char *c, int l){         //converts string c of len l to int
    int res=0;
    for(int i=0; i<l-1; i++){
        res*=10;
        res+=*c-'0';
        c++;
    }
    return res;
}


int get_records(){          //reads records from "records.txt"
    char c[7]={0};
    FILE *plik;
    plik=fopen("records.txt", "r");
    for(int i=0; i<3; i++){
        for(int j=0; j<10; j++){
          fgets(c, 7, plik);
          records[i][j]=(time_t) conv(c, strlen(c));
        }
    }
    if(fclose(plik))printf("Blad zamykania pliku\n");
    return 1;
}

int compare_time(time_t score, int lvl){
    for(int i=0; i<10; i++){
        if(score<=records[lvl-1][i]) return i;
    }
    return -1;
}

int new_records(time_t score, int n, int lvl){
    int i=n;
    int tmp=records[lvl-1][i];
    int tmp2;
    records[lvl-1][i]=score;
    while(i<9){
        tmp2=records[lvl-1][i+1];
        records[lvl-1][i+1]=tmp;
        i++;
        tmp=tmp2;
    }
    return 1;
}

int write_new_records(){
    FILE *plik;
    plik=fopen("records.txt", "w");
    for(int i=0; i<3; i++){
        for(int j=0; j<10; j++){
            fprintf(plik, "%ld\n", records[i][j]);
        }
    }
    if(fclose(plik))printf("Blad zamykania pliku\n");
    return 1;    
}
