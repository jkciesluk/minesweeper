#include "time_records.h"

time_t get_time(){
    return time(NULL);
}

time_t game_time(time_t t1, time_t t2){
    return t2-t1;
}

void print_time(time_t t){
    printf("%.2ld:%.2ld:%.2ld\n",t/3600, t%3600/60, t%60);
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

int print_records(){
    for(int i=0; i<10; i++){
      if(i<9)printf("%d.  " , i+1);
      else printf("%d. " , i+1);
      print_time(records[i]);
    }
    return 1;
}

int get_records(){
    char c[10][7]={0};
    FILE *plik;
    plik=fopen("records.txt", "r");
    for(int i=0; i<10; i++){
      fgets(c[i], 7, plik);
      records[i]=(time_t) conv(c[i], strlen(c[i]));
    }
    if(fclose(plik))printf("Blad zamykania pliku\n");
    return 1;
}

int compare_time(time_t score){
    for(int i=0; i<10; i++){
        if(score<=records[i]) return i;
    }
    return -1;
}

int new_records(time_t score, int n){
    int i=n;
    int tmp=records[i];
    int tmp2;
    records[i]=score;
    while(i<9){
        tmp2=records[i+1];
        records[i+1]=tmp;
        i++;
        tmp=tmp2;
    }
    return 1;
}

int write_new_records(){
    FILE *plik;
    plik=fopen("records.txt", "w");
    for(int i=0; i<10; i++){
        fprintf(plik, "%ld\n", records[i]);
    }
    if(fclose(plik))printf("Blad zamykania pliku\n");
    return 1;    
}
