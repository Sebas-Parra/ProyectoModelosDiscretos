/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
    typedef enum GameScreen {LOGO = 0, TITLE, GAMEPLAY, ENDING} GameScreen;
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // La primera ventana que se verá sera la del menú
    GameScreen currentScreen = LOGO;

    int framesCounter = 0; // por necesitmos medir el tiempo de espera

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        switch (currentScreen) {
        case LOGO:
            //Todo lo que tenga que venir en el logo de la app
            //Solo aqui van a ir los frames por segundo
            //En esta parte solo se debe esperar hasta que pase a la siguiente 
            //pestaña
            framesCounter++;
            if (framesCounter > 300) currentScreen = TITLE;
            break;
        case  TITLE:
            //Logica para todo lo que venga en el titulo de la app
            if(IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) currentScreen = GAMEPLAY;
            break;
        case GAMEPLAY:
            //Aqui va a ir toda la logica del juego en curso
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) currentScreen = ENDING;
            break;
        case ENDING:
            if (IsKeyPressed(KEY_ESCAPE)) break;
            break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        //Aqui es donde va a ir todo el diseño del juego
        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentScreen) {
        case LOGO:
            //Aqui es el diseño del logo
            DrawText("Bienvenido a este mundo!!", 300, 150, 30, BLACK);
            break;
        case  TITLE:
            //Diseño del titulo
            DrawText("Presiona Enter para continuar a la siguiente parte", 200, 150, 30, BLACK);
            break;
        case GAMEPLAY:
            //Diseño del juego en si
            DrawText("Aqui va el juego", 0,0,30,BLACK);
            break;
        case ENDING:
            //Diseño del final
            DrawText("Presiona ESC para salir",0,0,30,PINK);
            break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}