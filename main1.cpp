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
#include <cstring>
#include "Preguntas.h"
#include <vector>
#include <string>

//------------------------------------------------------------------------------------
// Program main entry point
    typedef enum GameScreen {LOGO = 0, TITLE, GAMEPLAY, ENDING, CHATBOT} GameScreen;

    bool IsMouseOverRectangle(int x, int y, int ancho, int alto) {
        Vector2 raton = GetMousePosition();
        return (raton.x > x && raton.x < x + ancho && raton.y > y && raton.y < y + alto);
    }
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Proyecto Grupol");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // La primera ventana que se verá sera la del menú
    GameScreen currentScreen = LOGO;

    int framesCounter = 0; // por necesitmos medir el tiempo de espera
    
    Preguntas preguntas("Aprendido.txt");
    const std::vector<std::string>& listaPreguntas = preguntas.obtenerPreguntas();
    const std::vector<std::string>& listaRespuestas = preguntas.obtenerRespuestas();
    int preguntaSeleccionada = -1;


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
            if (IsKeyPressed(KEY_C)) currentScreen = CHATBOT;
            break;
        case GAMEPLAY:
            //Aqui va a ir toda la logica del juego en curso
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) currentScreen = ENDING;
            break;
        case ENDING:
            if (IsKeyPressed(KEY_ESCAPE)) break;
            break;
        case CHATBOT:
            // Dibujar la lista de preguntas
            for (int i = 0; i < listaPreguntas.size(); i++) {
                if (IsMouseOverRectangle(10, 50 + i * 30, 780, 30)) {
                    DrawRectangle(10, 50 + i * 30, 780, 30, LIGHTGRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        preguntaSeleccionada = i;
                    }
                }
                DrawText(listaPreguntas[i].c_str(), 10, 50 + i * 30, 20, BLACK);
            }

            // Dibujar la respuesta seleccionada
            if (preguntaSeleccionada != -1) {
                DrawText("Pregunta:", 10, 350, 20, DARKGRAY);
                DrawText(listaPreguntas[preguntaSeleccionada].c_str(), 10, 380, 20, BLACK);
                DrawText("Respuesta:", 10, 410, 20, DARKGRAY);
                DrawText(listaRespuestas[preguntaSeleccionada].c_str(), 10, 440, 20, BLACK);
            }

            // Dibujar el botón de regreso
            if (IsMouseOverRectangle(650, 400, 120, 40)) {
                DrawRectangle(650, 400, 120, 40, GRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = TITLE;
                    preguntaSeleccionada = -1; // Resetear la selección al volver al título
                }
            }
            else {
                DrawRectangle(650, 400, 120, 40, LIGHTGRAY);
            }
            DrawText("Volver", 675, 410, 20, BLACK);
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
            DrawText("Presiona C para abrir el Chatbot", 200, 200, 30, BLACK);
            break;
        case GAMEPLAY:
            //Diseño del juego en si
            DrawText("Aqui va el juego", 0,0,30,BLACK);
            break;
        case ENDING:
            //Diseño del final
            DrawText("Presiona ESC para salir",0,0,30,PINK);
            break;
        case CHATBOT:
            DrawText("Chatbot", 10, 10, 20, DARKGRAY);

            // Dibujar la lista de preguntas
            for (int i = 0; i < listaPreguntas.size(); i++) {
                if (IsMouseOverRectangle(10, 50 + i * 30, 780, 30)) {
                    DrawRectangle(10, 50 + i * 30, 780, 30, LIGHTGRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        preguntaSeleccionada = i;
                    }
                }
                DrawText(listaPreguntas[i].c_str(), 10, 50 + i * 30, 20, BLACK);
            }

            // Dibujar la respuesta seleccionada
            if (preguntaSeleccionada != -1) {
                DrawText("Pregunta:", 10, 350, 20, DARKGRAY);
                DrawText(listaPreguntas[preguntaSeleccionada].c_str(), 10, 380, 20, BLACK);
                DrawText("Respuesta:", 10, 410, 20, DARKGRAY);
                DrawText(listaRespuestas[preguntaSeleccionada].c_str(), 10, 440, 20, BLACK);
            }

            // Dibujar el botón de regreso
            if (IsMouseOverRectangle(650, 400, 120, 40)) {
                DrawRectangle(650, 400, 120, 40, GRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = TITLE;
                    preguntaSeleccionada = -1; // Resetear la selección al volver al título
                }
            }
            else {
                DrawRectangle(650, 400, 120, 40, LIGHTGRAY);
            }
            DrawText("Volver", 675, 410, 20, BLACK);
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