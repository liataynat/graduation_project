#include "../include/init_signal.h"
#include <stdio.h>

void handle_interrupt(int sig) {
    cout << "c" << endl;
    cout << "c caught signal... exiting" << endl;

    if(best_step < LONG_LONG_MAX) {
        //check_best_solution();
        //output();
    } else cout << "c solution initialization not yet complete" << endl;
    //free_memory();
    exit(-1);
}//引用

void init_signal(){
    signal(SIGTERM, handle_interrupt);
    signal(SIGINT, handle_interrupt);
}