#include "../include/function_test.h"
#include "../include/init_argument.h"
#include "../include/init_signal.h"
#include "../include/basis.h"
#include <stdio.h>

int main(int argc, char **argv){
    init_argument(argc,argv);
    preprocessing();
    function_test();
    return 0;
}