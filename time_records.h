#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

time_t records[10];

time_t get_time();
time_t game_time(time_t t1, time_t t2);
void print_time(time_t t);
int conv(const char *c, int l);
int print_records();
int get_records();
int compare_time(time_t score);
int new_records(time_t score, int n);
int write_new_records();