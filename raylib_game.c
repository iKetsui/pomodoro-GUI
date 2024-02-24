
#include "raylib.h"
#include "screens.h"    // NOTE: Declares global (extern) variables and screens functions
#include <rlgl.h>
#include <time.h>
#include "title.c"
#include <stdio.h>
#include <stdlib.h>


typedef struct Timer {
    double startTime;   // Start time (seconds)
    double lifeTime;    // Lifetime (seconds)
} Timer;

Timer seconds = {0}; 

double countTo = 1200; //CHANGE THE TIMER HERE (BASED ON SECONDS) 

int secScreen = 0; //Visual Text


//still on test
int SEC = 0;
int MIN = 0;
int HOUR= 0;


void TimerFunction(){
    printf(" HOURS :%d , MINS :%d , SEC : %d \n" , HOUR ,MIN , SEC);
    } 


void DivisionFunction(){ // This Function Will Turn Seconds (countTo variable) into HOURS and MINS 

 int divisionfunc =  secScreen; 

SEC = divisionfunc% 60;
MIN = (divisionfunc / 60) % 60;
HOUR = (divisionfunc / 3600);



printf(" DIV: %d \n" , divisionfunc);
printf(" HOURS :%d , MINS :%d  SEC : %d\n" , HOUR ,MIN, SEC);

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



int main(void)
{
        int startTime = GetTime();
        int endTime = countTo - GetTime();

        printf("%d\n" , startTime);


    const int screenwidth = 900;
    const int screenheight = 500;


    InitAudioDevice();
    Music music = LoadMusicStream("assets/Alarm.wav");
    while (!IsWindowFocused)
    {
        music.looping = true;
        if (IsWindowFocused)
        {
            StopMusicStream(music);
        }
        

    }
    
    InitWindow(screenwidth, screenheight, "POMODORO");


    SetExitKey(KEY_NULL);
    bool exitWindowRequested = false;   
    bool exitWindow = false;    


    SetTargetFPS(60);


    while (!exitWindow){

       
       
      UpdateMusicStream(music); 




        if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {

            secScreen = GetReversedTime(seconds);

            StartTimer(&seconds, countTo); // Pass the address of seconds


    }


    if(!TimerDone(seconds)){

        secScreen = GetReversedTime(seconds);

        }

        if(secScreen == TimerDone(seconds)){
            PlayMusicStream(music);
            float timePlayed = 0.0f;
            music.looping = false;
            if (IsWindowFocused)
            {
                music.looping = false;
                if(IsKeyPressed(MOUSE_BUTTON_LEFT)){StopMusicStream(music);}
            }
            else{ music.looping = true;}
            

        }
    BeginDrawing();










    DrawRectangle(0,0 , screenwidth , screenheight , GRAY);
    DrawText("Press the SPACE or MOUSE'S LEFT CLICK to start" , 155 , 200 , 23 , WHITE);
   // DrawText("(1200 sec == 20 mins)" , 345 , 230 , 19 , WHITE);
    DrawText("Press the ESC to close the window" , 0 , 5 , 17 , BLACK);
    

   // DrawText(TextFormat("%d" , secScreen) , 420 , 255 , 35 , WHITE);   
    DrawText(TextFormat("%d:%d:%d" , HOUR , MIN , SEC) , 387 , 230 , 50 , WHITE);

    if (exitWindowRequested == true)
    {
        DrawRectangle(0 , 130 , 900, 200 , BLACK);
        DrawText("Are you Sure you want to close the program ?" , 100 , 210 , 30 , WHITE);
        DrawText("PRESS Y/N" , 350 , 260 , 25 , WHITE);

    }

    








    EndDrawing();


    DivisionFunction();

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
         


    }

    return 0;

}

