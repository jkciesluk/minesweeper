#include "time_records.h"

time_t get_time(){
    return time(NULL);
}

time_t game_time(time_t t1, time_t t2){
    return t1-t2;
}

void print_time(time_t t){
    printf("%.2ld:%.2ld\n", t/60, t%60);
}