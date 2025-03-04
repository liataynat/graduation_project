#ifndef BASIS
#define BASIS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <climits>
#include <cfloat>
#include <memory.h>
#include <sys/time.h>
#include <unistd.h>
#include <set>
#include <utility>


using namespace std;

#define mypop(stack) stack[--stack ## _fill_pointer]
#define mypush(item, stack) stack[stack ## _fill_pointer++] = item


//set(variable, soft clause) information
extern long long *time_stamp;
extern int *weight;
extern int *org_weight;
extern int *fix;
extern set<int> tabu_list;
extern int *zero_stack;
extern int zero_stack_fill_pointer;
extern int *index_in_zero_stack;

//variable(hard clause)
extern int *cover_count;
extern int *cover_set;
extern int *cover_set2;
extern int *uncover_stack;
extern int *index_in_uncover_stack;
extern int uncover_stack_fill_pointer;

//solution information
extern int *cur_solu;
extern long long cur_weight;
extern int reduce_weight;
extern int *best_solu;
extern long long best_weight;
extern double best_time;
extern long long best_step;
extern int *set_solu;
extern int *index_in_set_solu;
extern int set_count;

extern int *not_set_solu;
extern int *index_in_not_in_set_solu;
extern int not_set_count;

//data structure
extern int cutoff_time;
extern int BMS_T;
extern long long step;
extern long long max_step;

extern int item_num;
extern int set_num;

extern int *item_delete;
extern int *set_delete;
extern int **item_set;
extern int *item_set_num;
extern int *org_item_set_num;
extern int **set_var;
extern int *set_item_num;
extern int *org_set_item_num;

extern int mu;
extern double novel_addition_prob;

extern struct tms start_time;

#endif
