
#include "raylib.h"
#include "screens.h"    // NOTE: Declares global (extern) variables and screens functions
#include <rlgl.h>
#include <time.h>



int main(void)
{

    const int screenwidth = 900;
    const int screenheight = 500;

    InitWindow(screenwidth, screenheight, "POMODORO");

    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {


    BeginDrawing();
    DrawRectangle(0,0 , screenwidth , screenheight , GRAY);
    DrawText("Press the SPACE to start" , 250 , 200 , 25 , WHITE);
    DrawText("Press the ESC to close the window" , 260 , 150 , 17 , WHITE);

    if(KEY_SPACE == true){


    }
    EndDrawing();



    }
    if(KEY_ESCAPE == true){
    CloseWindow();
    }
    return 0;
}