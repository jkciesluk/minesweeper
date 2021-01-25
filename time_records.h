#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

time_t records[3][10];

time_t get_time();
time_t game_time(time_t t1, time_t t2);

int conv(const char *c, int l);
int get_records();
int compare_time(time_t score, int lvl);
int new_records(time_t score, int n, int lvl);
int write_new_records();