#include "time_records.h"

time_t get_time(){
    return time(NULL);
}

time_t game_time(time_t t1, time_t t2){
    return t1-t2;
}

void print_time(time_t t){
    printf("%.2ld:%.2ld:%.2ld\n",t/3600, t/60, t%60);
}

int conv(const char *c){
    int res=0;
    while(*c){
        res*=10;
        res+=*c-'0';
        c++;
    }
    return res;
}

int get_records(){
    char c[10][5];
    FILE *plik;
    plik=fopen("records.txt", "r");
    for(int i=0; i<10; i++){
        fgets(char[i], 5, plik);
        printf("%d ", conv(c[i]));       
    }
    return 1;
}
