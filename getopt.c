#include "raylib.h"
#include "screens.h"    // NOTE: Declares global (extern) variables and screens functions
#include <rlgl.h>
#include <time.h>
#include "title.c"
#include <stdio.h>
#include <stdlib.h>
#include "getopt.h"
#include "global.h"


int t(int argc , char **argv){
    opterr = 0 ;
    int c;
    int s;

    while((c = getopt(argc , argv , "s:")) != -1) {

        switch (c)
        {
        case 's':
            countTo = c;
            break;
        
        default: 
            break;
        }
    }
    return 0;
}