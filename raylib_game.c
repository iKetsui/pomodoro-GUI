
#include <global.h>
#include "raylib.h"
#include "screens.h"    // NOTE: Declares global (extern) variables and screens functions
#include <rlgl.h>
#include <time.h>
#include "title.c"
#include <stdio.h>
#include <stdlib.h>
#include "getopt.c"
#include "reasings.h"
#include "math.h"

#define RAYGUI_IMPLEMENTATION

#include "raygui.h"

Timer seconds = {0};


int secScreen = 0; //Visual Text
int countTo = 1200; //CHANGE THE TIMER HERE (BASED ON SECONDS) 


/*DO NOT TOUCH*/ 
int SEC = 0;
int MIN = 0;
int HOUR= 0;
/*DO NOT TOUCH*/ 



void DivisionFunction(){ // This Function Will Turn Seconds (countTo variable) into HOURS and MINS 


 int divisionfunc =  secScreen; 
 

SEC = divisionfunc% 60;
MIN = (divisionfunc / 60) % 60;
HOUR = (divisionfunc / 3600);

float guiCountTo = 10.0f;

if(SEC > 0){
printf(" DIV: %d \n" , divisionfunc);
printf(" HOURS :%d , MINS :%d  SEC : %d\n" , HOUR ,MIN, SEC);
}
}


void StartTimer(Timer *timer, double lifetime)
{
    timer->startTime = GetTime();
    timer->lifeTime = lifetime;
}

bool TimerDone(Timer timer)
{
    return GetTime() - timer.startTime >= timer.lifeTime;
}

double GetElapsed(Timer timer)
{
    return GetTime() - timer.startTime;
}

int GetReversedTime(Timer timer)
{
    int reversed = abs(GetElapsed(seconds) - countTo);

    return reversed; 
}

void ResetTimer(Timer *timer, double lifetime)
{
    timer->startTime = GetTime();
    timer->lifeTime = lifetime;
}

float easeInSine(float num) {

  return 1 - cos((num* PI) / 2);
}

float lerp (float a , float b , float t1 , float t2){

  return (a + (t1/t2)* (b - a));  
  }


// MAIN FUNCTION --------------------------------------------------------------------------------------------------------------------
int main(int argc , char **argv)
{
    secScreen = GetReversedTime(seconds);
    
    getoptFunction(argc , argv);

        int startTime = GetTime();
        int endTime = countTo - GetTime();

        printf("%d\n" , startTime);


    const int screenwidth = 925;
    const int screenheight = 500;

    float time1 = secScreen/countTo; 
    float width = 0;
    int height = screenheight;
    float per = fmod(GetElapsed(seconds), countTo);
    InitAudioDevice(); 
    Music music = LoadMusicStream("assets/Alarm.wav");
   
    
    InitWindow(screenwidth, screenheight, "POMODORO");


    SetExitKey(KEY_NULL);
    bool exitWindowRequested = false;   
    bool exitWindow = false;

    SetTargetFPS(60);

    DivisionFunction();

    int periods = 0;

    int framesElapesd = 0;
    int xBall = (screenwidth+150);
    int yBall = (screenheight+390);

    int radBall = 20;

    while (!exitWindow){

       
       
      UpdateMusicStream(music); 
        
        



        if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
            periods = 1;
            framesElapesd = 0;
            secScreen = GetReversedTime(seconds);
            music.looping = false;

            StartTimer(&seconds, countTo); // Pass the address of seconds


    }


    if(!TimerDone(seconds)){
        
        secScreen = GetReversedTime(seconds);

        }

        if(secScreen == TimerDone(seconds)){
            PlayMusicStream(music);
            float timePlayed = 0.0f;
            music.looping = true;
            periods = 3;
            framesElapesd = 0;
            if (IsWindowMinimized)
            {
                music.looping = true;
                if(!IsWindowMinimized){ music.looping = false;}
            }
            

        }


    
        if(periods == 0){
            ClearBackground(DARKGRAY);

            DrawText("Press the SPACE or touch the Screen to start" , 155 , 200 , 23 , WHITE);
            DrawText("Press the ESC to close the window" , 0 , 5 , 17 , BLACK);
    
            DrawText(TextFormat("%d:%d:%d" , HOUR , MIN , SEC) , 370 , 230 , 50 , WHITE);
              DrawRectangle(0 , screenheight-3 , width , 20 , WHITE);
                  

            printf("%d \n" , framesElapesd);


    }else if(periods == 1){
            ClearBackground(DARKGRAY);
            DrawText("Press the SPACE or touch the Screen to start" , 155 , 200 , 23 , WHITE);
            DrawText("Press the ESC to close the window" , 0 , 5 , 17 , BLACK);


        framesElapesd++;
        radBall = (int)EaseElasticOut((float) framesElapesd , 200 , 1000 , 1500);

    if (framesElapesd >= 140)
    {
        periods = 2;
        framesElapesd = 0;
        xBall = (screenwidth+120);
        yBall = (screenheight+165);
        radBall = 20;



    }
    } else if(periods == 2){
        framesElapesd++;
        ClearBackground(RED);


        DrawText("Press the SPACE or touch the Screen to start" , 155 , 200 , 23 , WHITE);
        DrawText("Press the ESC to close the window" , 0 , 5 , 17 , BLACK);


        DrawText(TextFormat("%d:%d:%d" , HOUR , MIN , SEC) , 370 , 230 , 50 , WHITE);
              DrawRectangle(0 , screenheight-3 , width , 20 , WHITE);
              width = lerp(0, screenwidth , secScreen , countTo);
              printf("width : %f" , width);


    }else if(periods == 3){
        framesElapesd++;
        ClearBackground(RED);


        DrawText("Press the SPACE or touch the Screen to start" , 155 , 200 , 23 , WHITE);
        DrawText("Press the ESC to close the window" , 0 , 5 , 17 , BLACK);


        DrawText(TextFormat("%d:%d:%d" , HOUR , MIN , SEC) , 370 , 230 , 50 , WHITE);
                      DrawRectangle(0 , screenheight-3 , width , 20 , WHITE);
              width = lerp(0, screenwidth , secScreen , countTo);
              

        radBall = (int)EaseElasticOut((float) framesElapesd , 200 , 1000 , 1500);
        if(framesElapesd >= 140){
            periods = 4;
            framesElapesd = 0;
            xBall = (screenwidth+150);
            yBall = (screenheight+390);
            radBall = 20;

        }
        

    }else if(periods == 4){
        framesElapesd++;
        ClearBackground(PURPLE);


        DrawText("Press the SPACE or touch the Screen to start" , 155 , 200 , 23 , WHITE);
        DrawText("Press the ESC to close the window" , 0 , 5 , 17 , BLACK);


        DrawText(TextFormat("%d:%d:%d" , HOUR , MIN , SEC) , 370 , 230 , 50 , WHITE);
                      DrawRectangle(0 , screenheight-1 , width , 20 , WHITE);
              width = lerp(0, screenwidth , secScreen , countTo);



    }


        // DRAWING SECTION ------------------------------------------------------------------------
    BeginDrawing();
if(periods == 1 ){

    printf("%d\n",framesElapesd);
    ClearBackground(DARKGRAY);
    DrawCircle(xBall , yBall , radBall , RED);


    DrawText("Press the SPACE or touch the Screen to start" , 155 , 200 , 23 , WHITE);
    DrawText("Press the ESC to close the window" , 0 , 5 , 17 , BLACK);
    DrawText(TextFormat("%d:%d:%d" , HOUR , MIN , SEC) , 370 , 230 , 50 , WHITE);
              DrawRectangle(0 , screenheight-1 ,(float) width , 20 , WHITE);
              width = lerp(0, screenwidth , secScreen , countTo);
              printf("width : %f" , width);

    
}else if(periods == 3 ){

    printf("period 3: %d\n",framesElapesd);
    DrawCircle(xBall , yBall , radBall , PURPLE);


    DrawText("Press the SPACE or touch the Screen to start" , 155 , 200 , 23 , WHITE);
    DrawText("Press the ESC to close the window" , 0 , 5 , 17 , BLACK);
    DrawText(TextFormat("%d:%d:%d" , HOUR , MIN , SEC) , 370 , 230 , 50 , WHITE);
    

    
}
/*

    ClearBackground(GRAY);


    float guiCountTo = 450.0f;
   
    printf("%2.f\n" , guiCountTo);

    GuiSliderPro((Rectangle){ 600, 50, 150, 20 }, "SECONDS", NULL, &guiCountTo, 0, 450 , 10);


    DrawText("Press the SPACE or MOUSE'S LEFT CLICK to start" , 155 , 200 , 23 , WHITE);
    DrawText("Press the ESC to close the window" , 0 , 5 , 17 , BLACK);
    



    DrawText(TextFormat("%d:%d:%d" , HOUR , MIN , SEC) , 387 , 230 , 50 , WHITE);
*/
    if (exitWindowRequested == true)
    {
        
        DrawRectangle(0 , 130 , 900, 200 , Fade(BLACK , 0.90f));
        DrawText("Are you Sure you want to close the program ?" , 100 , 210 , 30 , WHITE);
        DrawText("PRESS Y/N" , 350 , 260 , 25 , WHITE);

    }

    






    //DivisionFunction();



    EndDrawing();






        if(WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;

        if(exitWindowRequested){
            if (IsKeyPressed(KEY_Y))
            {
                exitWindow = true;
            } 
            if (IsKeyPressed(KEY_N))
            {
                exitWindowRequested = false;
            }
        }
            
            
        // pop up text to confirm the exit
        if(exitWindow){
        UnloadMusicStream(music);          // Unload music stream buffers from RAM

        CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)

        CloseWindow();
        }
         

    DivisionFunction();

    }

    return 0;

}

