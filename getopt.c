#include "raylib.h"
#include "screens.h"    // NOTE: Declares global (extern) variables and screens functions
#include <rlgl.h>
#include <time.h>
#include "title.c"
#include <stdio.h>
#include <stdlib.h>
#include "getopt.h"
#include "global.h"


static void getoptFunction(int argc , char **argv){

    opterr = 0 ;
    int c = 0;
    int s;
    char *svalue = NULL;

    while((c = getopt(argc , argv , "s:t")) != -1) {

        int passer = 1;
        switch (c)
        {
        case 's':
        printf("%s \n" , optarg);
        countTo = atoi(optarg);
            break;

        case 't':
        printf("TEST\n") ;
        
        default: 
        printf("Use -s parameter in order to change the seconds value, otherwise, the program will default be 1200secs - 20m - .\n");
            break;
        }
    }
}