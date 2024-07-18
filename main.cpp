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
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Texture2D personaje = LoadTexture("knight_run_spritesheet.png");
    Texture2D mesa1 = LoadTexture("mesa1.png");

    int frameWight = personaje.width/6; //Hay 6 cuadros de animacion
    int frameHeight = personaje.height; //Altura de un solo cuadro de animacion

    Rectangle frameRec = {0.0f,0.0f,(float)frameWight,(float)frameHeight};

    Vector2 personajePosicion = {(float)screenWidth/2 - frameWight/2, (float)screenHeight/2 - frameHeight/2};

    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8; //velocidad de la animacion
    
    float scale = 6.0f;
    float personajeVel = 4.0f;
    float mesaScale1 = 0.2f;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        framesCounter++;
        if(framesCounter >= (60 / framesSpeed)){
            framesCounter = 0;
            currentFrame++;

            if(currentFrame > 5) currentFrame = 0; //hay 6 uadros de animacion

            frameRec.x = (float)currentFrame * frameWight;

        }
        //----------------------------------------------------------------------------------

        //Movimiento del personaje
        if (IsKeyDown(KEY_RIGHT)) personajePosicion.x += personajeVel;
        if (IsKeyDown(KEY_LEFT)) personajePosicion.x -= personajeVel;
        if (IsKeyDown(KEY_UP)) personajePosicion.y -= personajeVel;
        if (IsKeyDown(KEY_DOWN)) personajePosicion.y += personajeVel;
        //------------------------------

        // Draw

        
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            //Detecta si el personaje está cerca de la mesa
            Rectangle mesa1Rec = {0.0f,0.0f,(float)mesa1.width,(float)mesa1.height};
            Rectangle mesa1DestRec = { 10,10, mesa1.width * mesaScale1, mesa1.height * mesaScale1 };
            Vector2 origin = { 0.0f, 0.0f };
            Rectangle personajeRec = { personajePosicion.x - (frameWight * scale) / 2, personajePosicion.y - (frameHeight * scale) / 2, frameWight * scale, frameHeight * scale };
            bool cercaDeMesa = CheckCollisionRecs(personajeRec, mesa1DestRec);

            DrawTexturePro(mesa1,mesa1Rec,mesa1DestRec,origin,0.0f,WHITE);

            Rectangle destRec = {personajePosicion.x,personajePosicion.y,frameWight * scale, frameHeight * scale};
            Vector2 Personajeorigin = {frameWight/2.0f,frameHeight/2.0f};
            DrawTexturePro(personaje,frameRec,destRec,Personajeorigin,0.0f,WHITE);

            Rectangle botonRec = {screenWidth / 2- 100, screenHeight / 2+ 80, 200,40};
            bool botonPresionado = false;

            if(cercaDeMesa && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botonRec)){
                botonPresionado = true;
            }

            if (cercaDeMesa)
            {
                DrawText("¿Quieres hacer algo en la mesa?", screenWidth / 2 - MeasureText("¿Quieres hacer algo en la mesa?", 20) / 2, screenHeight / 2 + 50, 20, RED);
                DrawRectangleRec(botonRec, LIGHTGRAY);
                DrawText("Sí", screenWidth / 2 - MeasureText("Sí", 20) / 2, screenHeight / 2 + 90, 20, BLACK);
            }

            if (botonPresionado)
            {
                DrawText("Haciendo algo en la mesa...", screenWidth / 2 - MeasureText("Haciendo algo en la mesa...", 20) / 2, screenHeight / 2 - 20, 20, BLUE);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(personaje);
    UnloadTexture(mesa1);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}