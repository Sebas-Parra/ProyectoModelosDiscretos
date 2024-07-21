#include "raylib.h"
#include <cstring>
#include "Preguntas.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>

//------------------------------------------------------------------------------------
// Program main entry point
typedef enum GameScreen { LOGO = 0, GAMEPLAY,PREGUNTAS, CHATBOT } GameScreen;

bool IsMouseOverRectangle(int x, int y, int ancho, int alto) {
    Vector2 raton = GetMousePosition();
    return (raton.x > x && raton.x < x + ancho && raton.y > y && raton.y < y + alto);
}


//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800; // Ancho
    const int screenHeight = 450; // Altura

    InitWindow(screenWidth, screenHeight, "Proyecto Grupol");
    SetWindowState(FLAG_WINDOW_RESIZABLE); // Hacer la ventana redimensionable

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // La primera ventana que se verá sera la del menú
    GameScreen currentScreen = LOGO;

    int framesCounter = 0; // por necesitmos medir el tiempo de espera

    Preguntas preguntas("Aprendido.txt");
    const std::vector<std::string>& listaPreguntas = preguntas.obtenerPreguntas();
    const std::vector<std::string>& listaRespuestas = preguntas.obtenerRespuestas();
    std::string preguntaUsuario = "";
    std::string respuesta = "";
    bool preguntaSeleccionadaFlag = false;
    std::string lineaRand = "";

    // Aqui se crea el personaje
    Texture2D personaje = LoadTexture("knight_run_spritesheet.png");
    Vector2 personajePos = { (float)screenWidth / 2,(float)screenHeight / 2 };
    float velocidadBol = 4.0f;
    float scalaP = 2.0f;
    int frameWidthP = personaje.width / 6;;// Asumiendo que hay 6 frames en la animación
    int frameHeightP = personaje.height;
    Rectangle sourceRecP = { 0.0f,0.0f,(float)frameWidthP,(float)frameHeightP };
    Rectangle destRecP = { personajePos.x,personajePos.y,frameWidthP * scalaP,frameHeightP * scalaP };
    Vector2 originP = { (frameWidthP * scalaP) / 2.0f, (frameHeightP * scalaP) / 2.0f };
    float Rotation = 0.0f;
    int framesCouter = 0;
    int currentframes = 0;
    // Aqui se crean los demas objetos
    Texture2D mesa1 = LoadTexture("mesa1.png");
    Texture2D mesa2 = LoadTexture("mesa2.png");
    Texture2D mesa3 = LoadTexture("mesa3.png");
    Texture2D mesa4 = LoadTexture("mesa4.png");
    //mesa1
    Vector2 mesa1Pos = { (float)screenWidth - 730,(float)screenHeight - 395 };
    int frameWidthM1 = mesa1.width;
    int frameHeightM1 = mesa1.height;
    float scalaM1 = 2.0f;
    Rectangle sourceRecM1 = { 0.0f,0.0f,(float)frameWidthM1,(float)frameHeightM1 };
    Rectangle destRecM1 = { mesa1Pos.x,mesa1Pos.y,frameWidthM1 * scalaM1, frameHeightM1 * scalaM1 };
    Vector2 originM1 = { (frameWidthM1*scalaM1)/2.0f,(frameHeightM1*scalaM1)/2.0f };
    float rotation = -45.0f;
    //mesa2
    Vector2 mesa2Pos = { (float)screenWidth -  450,(float)screenHeight - 445};
    int frameWidthM2 = mesa2.width;
    int frameHeightM2 = mesa2.height;
    float scalaM2 = 2.0f;
    Rectangle sourceRecM2 = { 0.0f,0.0f,(float)frameWidthM1,(float)frameHeightM1 };
    Rectangle destRecM2 = { mesa2Pos.x,mesa2Pos.y,frameWidthM2 * scalaM2, frameHeightM2 * scalaM2 };
    Vector2 originM2 = { 0.0f,0.0f };
    float rotationM2 = 0.0f;
    //mesa3
    Vector2 mesa3Pos = { (float)screenWidth - 70,(float)screenHeight - 290 };
    int frameWidthM3 = mesa3.width;
    int frameHeightM3 = mesa3.height;
    float scalaM3 = 2.0f;
    Rectangle sourceRecM3 = { 0.0f,0.0f,(float)frameWidthM1,(float)frameHeightM1 };
    Rectangle destRecM3 = { mesa3Pos.x,mesa3Pos.y,frameWidthM3 * scalaM3, frameHeightM3 * scalaM3 };
    Vector2 originM3 = { (frameWidthM3 * scalaM3) / 2.0f,(frameHeightM3 * scalaM3) / 2.0f };
    float rotationM3 = 45.0f;
    //mesa4
    Vector2 mesa4Pos = { (float)screenWidth - 750,(float)screenHeight - 200 };
    int frameWidthM4 = mesa4.width;
    int frameHeightM4 = mesa4.height;
    float scalaM4 = 2.0f;
    Rectangle sourceRecM4 = { 0.0f,0.0f,(float)frameWidthM4,(float)frameHeightM4 };
    Rectangle destRecM4 = { mesa4Pos.x,mesa4Pos.y,frameWidthM4 * scalaM4, frameHeightM4 * scalaM4 };
    Vector2 originM4 = { (frameWidthM4 * scalaM4) / 2.0f,(frameHeightM4 * scalaM4) / 2.0f };
    float rotationM4 = 45.0f;

    //----------------------------------------------------------------------------
    Rectangle botonPregunta = { screenWidth - 799,screenHeight - 20,110,40 };
    Rectangle botonRegresoGameplay = { screenWidth - 790, screenHeight - 440,90,40 };
    Rectangle botonInfo = { screenWidth - 790, screenHeight - 50, 85,35 };
    Rectangle cuadroInfo = { screenWidth - 790, screenHeight - 150, 50,50 };

    Rectangle botonResp1 = { screenWidth - 690, screenHeight - 320, 20,20 };
    Rectangle botonResp2 = { screenWidth - 690,screenHeight - 290, 20, 20 };
    Rectangle botonResp3 = { screenWidth - 690, screenHeight - 260, 20, 20 };
    Rectangle botonResp4 = { screenWidth - 690,screenHeight - 230,20,20 };
    //---------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        switch (currentScreen) {
        case LOGO:
            // Todo lo que tenga que venir en el logo de la app
            // Solo aqui van a ir los frames por segundo
            // En esta parte solo se debe esperar hasta que pase a la siguiente 
            // pestaña
            // framesCounter++;
            // if (framesCounter > 300) currentScreen = TITLE;
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) currentScreen = GAMEPLAY;
            if (IsKeyPressed(KEY_C)) currentScreen = CHATBOT;
            break;
        case GAMEPLAY: {
            // Aqui va a ir toda la logica del juego en curso
            framesCounter++;
            if (framesCounter >= (60 / 8)) {
                framesCounter = 0;
                currentframes++;

                if (currentframes > 5) currentframes = 0;
                sourceRecP.x = (float)currentframes * frameWidthP;
            }
            if (IsKeyDown(KEY_RIGHT) && personajePos.x < 799) personajePos.x += velocidadBol;
            if (IsKeyDown(KEY_LEFT) && personajePos.x > 1) personajePos.x -= velocidadBol;
            if (IsKeyDown(KEY_UP) && personajePos.y > 1) personajePos.y -= velocidadBol;
            if (IsKeyDown(KEY_DOWN) && personajePos.y < 449) personajePos.y += velocidadBol;
            //if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) currentScreen = ENDING;

            

            break;
        }
        case PREGUNTAS:
            if (IsMouseOverRectangle(botonRegresoGameplay.x, botonRegresoGameplay.y, botonRegresoGameplay.width, botonRegresoGameplay.height)
                && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                currentScreen = GAMEPLAY;
                lineaRand = "";
                preguntaSeleccionadaFlag = false;
            }

            

            break;
        case CHATBOT: {
            // Campo de texto para la pregunta del usuario
            static char text[256] = { 0 }; // Inicializa el texto vacío
            static int textLength = 0;

            // Captura la entrada del teclado
            int key = GetCharPressed();
            while (key > 0) {
                // Solo capturamos caracteres imprimibles, incluyendo caracteres especiales
                if ((key >= 32) && (key <= 126) || (key >= 192 && key <= 255) ) {
                    if (textLength < sizeof(text) - 1) {
                        text[textLength++] = (char)key;
                        text[textLength] = '\0'; // Aseguramos que el texto esté terminado en nulo
                    }
                }
                key = GetCharPressed(); // Captura el siguiente carácter
            }

            // Manejo del retroceso
            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (textLength > 0) {
                    textLength--;
                    text[textLength] = '\0'; // Aseguramos que el texto esté terminado en nulo
                }
            }

            // Manejo de envío del texto
            if (IsKeyPressed(KEY_ENTER)) {
                preguntaUsuario = text;
                // Busca la pregunta en la lista
                bool encontrada = false;
                for (int i = 0; i < listaPreguntas.size(); i++) {
                    if (preguntaUsuario == listaPreguntas[i]) {
                        respuesta = listaRespuestas[i];
                        encontrada = true;
                        break;
                    }
                }
                if (!encontrada) {
                    respuesta = "No se la respuesta a tu pregunta.";
                }
                textLength = 0; // Limpiar el campo de texto
            }

            // Mostrar el campo de texto
            DrawRectangle(10, 50, 780, 40, LIGHTGRAY);
            DrawText(text, 20, 55, 20, DARKGRAY);

            // Mostrar la respuesta de la pregunta
            DrawText("Respuesta:", 10, 100, 20, DARKGRAY);
            DrawText(respuesta.c_str(), 10, 130, 20, BLACK);

            
            break;
        }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        // Aqui es donde va a ir todo el diseño del juego
        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentScreen) {
        case LOGO:
            // Aqui es el diseño del logo
            DrawText("Bienvenido a este mundo!!", screenWidth-600, 150, 30, BLACK);
            DrawText("Presiona Enter para controlar bot", 120, 200, 30, BLACK);
            DrawText("Presiona C para abrir el Chatbot", 130, 250, 30, BLACK);
            {
                int textWidth = MeasureText("Presiona ESC para salir", 30);
                int screenW = GetScreenWidth();
                int screenH = GetScreenHeight();
                DrawText("Presiona ESC para salir", screenW - textWidth - 10, screenH - 40, 30, PINK);
            }
            break;
        case GAMEPLAY:
            // Diseño del juego en si
            destRecP.x = personajePos.x;
            destRecP.y = personajePos.y;
            DrawTexturePro(personaje, sourceRecP, destRecP, originP, Rotation, WHITE);
            DrawTexturePro(mesa1, sourceRecM1, destRecM1, originM1, rotation, WHITE);
            DrawTexturePro(mesa2,sourceRecM2,destRecM2,originM2,rotationM2,WHITE);
            DrawTexturePro(mesa3, sourceRecM3, destRecM3, originM3, rotationM3, WHITE);
            DrawTexturePro(mesa4, sourceRecM4, destRecM4, originM4, rotationM4, WHITE);
            // Dibujar el botón de regreso
            {
                int screenW = GetScreenWidth();
                int screenH = GetScreenHeight();
                if (IsMouseOverRectangle(screenW - 130, 10, 120, 40)) {
                    DrawRectangle(screenW - 130, 10, 120, 40, GRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        currentScreen = LOGO;
                        preguntaUsuario = "";
                        respuesta = "";
                    }
                }
                else {
                    DrawRectangle(screenW - 130, 10, 120, 40, LIGHTGRAY);
                }
                DrawText("Volver", screenW - 105, 20, 20, BLACK);
                // Mostrar el texto para salir
                int textWidth = MeasureText("Presiona ESC para salir", 20);
                DrawText("Presiona ESC para salir", screenW - textWidth - 10, screenH - 40, 20, PINK);
            }


            if (CheckCollisionRecs(destRecP, destRecM1)) {
                botonPregunta.x = 800 - 790;
                botonPregunta.y = 450 - 50;
                DrawRectangleRec(botonPregunta, BLUE);
                DrawText("Responder", screenWidth-790,screenHeight-41,20,BLACK);
                if (IsMouseOverRectangle(botonPregunta.x, botonPregunta.y, botonPregunta.width, botonPregunta.height) &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentScreen = PREGUNTAS;
                }
            }
            else if (CheckCollisionRecs(destRecP, destRecM2)) {
                botonPregunta.x = 800 - 790;
                botonPregunta.y = 450 - 50;
                DrawRectangleRec(botonPregunta, BLUE);
                DrawText("Responder", screenWidth - 790, screenHeight - 41, 20, BLACK);
                if (IsMouseOverRectangle(botonPregunta.x, botonPregunta.y, botonPregunta.width, botonPregunta.height) &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentScreen = PREGUNTAS;
                }
            }
            else if (CheckCollisionRecs(destRecP, destRecM3)) {
                botonPregunta.x = 800 - 790;
                botonPregunta.y = 450 - 50;
                DrawRectangleRec(botonPregunta, BLUE);
                DrawText("Responder", screenWidth - 790, screenHeight - 41, 20, BLACK);
                if (IsMouseOverRectangle(botonPregunta.x, botonPregunta.y, botonPregunta.width, botonPregunta.height) &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentScreen = PREGUNTAS;
                }
            }
            else if (CheckCollisionRecs(destRecP, destRecM4)) {
                botonPregunta.x = 800 - 790;
                botonPregunta.y = 450 - 50;
                DrawRectangleRec(botonPregunta, BLUE);
                DrawText("Responder", screenWidth - 790, screenHeight - 41, 20, BLACK);
                if (IsMouseOverRectangle(botonPregunta.x, botonPregunta.y, botonPregunta.width, botonPregunta.height) &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentScreen = PREGUNTAS;
                }
            }
            break;
        case PREGUNTAS: {
            if(!preguntaSeleccionadaFlag){
            std::ifstream archivo("Aprendido.txt");
            if (!archivo.is_open()) {
                std::cerr << "No se pudo abrir el archivo: " << std::endl;
                return 1;
            }

            std::string linea;
            std::vector<std::string> LineaPregunta;
            int lineaNumero = 0;
            while (std::getline(archivo, linea)) {
                if (linea.find('¿') != std::string::npos) {
                    LineaPregunta.push_back(linea);
                }
            }

            std::srand(std::time(nullptr));
            int indice = std::rand() % LineaPregunta.size();
            lineaRand = LineaPregunta[indice];
            archivo.close();

            preguntaSeleccionadaFlag = true;          
            }
            const char* lin = lineaRand.c_str();
            DrawText(lin, screenWidth - 690, screenHeight - 350, 20, BLACK);
            DrawRectangleRec(botonRegresoGameplay, BLUE);
            DrawText("Volver", screenWidth - 780, screenHeight - 435, 20, BLACK);
            DrawRectangleRec(botonInfo, GREEN);
            DrawText("Ayuda", screenWidth - 780, screenHeight - 40, 20, BLACK);
            if (CheckCollisionPointRec(GetMousePosition(), botonInfo)) {
                DrawRectangleRec(cuadroInfo, GREEN);
            }
            DrawRectangleRec(botonResp1, BLACK);
            DrawRectangleRec(botonResp2, BLACK);
            DrawRectangleRec(botonResp3, BLACK);
            DrawRectangleRec(botonResp4, BLACK);
            break;
        }
        case CHATBOT:
            DrawText("Hola, soy Chatbot. Escribe tu pregunta:", 10, 10, 20, DARKGRAY);
            
            // Dibujar el botón de regreso
            {
                int screenW = GetScreenWidth();
                int screenH = GetScreenHeight();
                if (IsMouseOverRectangle(screenW - 130, 10, 120, 40)) {
                    DrawRectangle(screenW - 130, 10, 120, 40, GRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        currentScreen = LOGO;
                        preguntaUsuario = "";
                        respuesta = "";
                    }
                }
                else {
                    DrawRectangle(screenW - 130, 10, 120, 40, LIGHTGRAY);
                }
                DrawText("Volver", screenW - 105, 20, 20, BLACK);
                // Mostrar el texto para salir
                int textWidth = MeasureText("Presiona ESC para salir", 20);
                DrawText("Presiona ESC para salir", screenW - textWidth - 10, screenH - 40, 20, PINK);
            }
            break;
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(personaje);
    UnloadTexture(mesa1);
    UnloadTexture(mesa2);
    UnloadTexture(mesa3);
    UnloadTexture(mesa4);
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
