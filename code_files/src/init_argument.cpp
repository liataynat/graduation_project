#include "../include/init_argument.h"
#include "../include/init_signal.h"
#include <stdio.h>

void init_argument(int argc, char **argv){
    init_signal();

    if(!parse_argument(argc,argv)){
        cout << "argument error" << endl;
        return ;
    };

    best_step = LONG_LONG_MAX;
    rng.seed(seed);

    return ;
}

bool parse_argument(int argc,char **argv){

}//好多啊