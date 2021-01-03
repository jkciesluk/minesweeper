#include "time_records.h"

time_t get_time(){
    return time(NULL);
}

time_t game_time(time_t t1, time_t t2){
    return t1-t2;
}

void print_time(time_t t){
    printf("%.2ld:%.2ld:%.2ld\n",t/3600, t%3600/60, t%60);
}

int conv(const char *c, int l){
    int res=0;
    for(int i=0; i<l-1; i++){
        res*=10;
        res+=*c-'0';
        c++;
    }
    return res;
}

int get_records(){
    char c[10][7]={0};
    FILE *plik;
    plik=fopen("records.txt", "r");
    for(int i=0; i<10; i++){
      fgets(c[i], 7, plik);
      if(i<9)printf("%d.  " , i+1);
      else printf("%d. " , i+1);
      print_time((time_t) conv(c[i], strlen(c[i])));
    }
    return 1;
}
