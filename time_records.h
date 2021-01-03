#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

time_t get_time();
time_t game_time(time_t t1, time_t t2);
void print_time(time_t t);
int conv(const char *c, int l);
int get_records();