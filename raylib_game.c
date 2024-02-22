
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
double countTo = 1200;
int secScreen = 1200;




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

double GetReversedTime(Timer timer)
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


    
    SetTargetFPS(60);


    while (!WindowShouldClose()){

       
       
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
    DrawText("Press the SPACE to start" , 280 , 200 , 25 , WHITE);
    DrawText("(1200 sec == 20 mins)" , 335 , 230 , 20 , WHITE);
    DrawText("Press the ESC to close the window" , 0 , 5 , 17 , BLACK);

    DrawText(TextFormat("%d" , secScreen) , 420 , 255 , 35 , WHITE);
    







    EndDrawing();


        

        if(IsKeyPressed(KEY_ESCAPE)){
        // pop up text to confirm the exit
        UnloadMusicStream(music);          // Unload music stream buffers from RAM

        CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)

        CloseWindow();
    
         }


    }

    return 0;

}

