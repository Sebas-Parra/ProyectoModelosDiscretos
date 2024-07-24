#include "raylib.h"
#include <cstring>
#include "Preguntas.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
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

    InitWindow(screenWidth, screenHeight, "Proyecto Grupal");
    InitAudioDevice();

    Music musica = LoadMusicStream("musicaFondo.mp3");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    PlayMusicStream(musica);
    // La primera ventana que se verá sera la del menú
    GameScreen currentScreen = LOGO;

    int framesCounter = 0; // por necesitmos medir el tiempo de espera

    Preguntas preguntas("Aprendido.txt");
    const std::vector<std::string>& listaPreguntas = preguntas.obtenerPreguntas();
    const std::vector<std::string>& listaRespuestas = preguntas.obtenerRespuestas();
    const std::vector<std::vector<std::string>>& listaOpciones = preguntas.obtenerOpciones();
    std::string preguntaUsuario = "";
    int preguntaIndex = 0;
    std::string respuesta = "";
    bool preguntaSeleccionadaFlag = false;
    std::string lineaRand = "";
    bool respuestaSeleccionadaFLag = false;
    int respSelec = -1; //No se ha seleccionado ninguna respuesta
    bool mostrarResultado = false;
    bool respuestaCorrecta = false;
    float tiempoInicio = 0.0f;
    std::string letra = "";

    Preguntas chatBot("Preguntas.txt");

    // Aqui se crea el personaje
    Texture2D personaje = LoadTexture("Robot.png");
    Vector2 personajePos = { (float)screenWidth / 2,(float)screenHeight / 2 };
    float velocidadBol = 4.0f;
    float scalaP = 2.5f;
    int frameWidthP = personaje.width / 8;// Asumiendo que hay 8 frames en la animación
    int frameHeightP = personaje.height;
    Rectangle sourceRecP = { 0.0f,0.0f,(float)frameWidthP,(float)frameHeightP };
    Rectangle destRecP = { personajePos.x,personajePos.y,frameWidthP * scalaP,frameHeightP * scalaP };
    Vector2 originP = { (frameWidthP * scalaP) / 2.0f, (frameHeightP * scalaP) / 2.0f };
    float Rotation = 0.0f;
    int framesCouter = 0;
    int currentframes = 0;
    // Aqui se crean los demas objetos
    Texture2D menuPrincipal = LoadTexture("menu.png");
    Texture2D fondo = LoadTexture("pantalla_principal.png");
    Texture2D mesa1 = LoadTexture("mesa1.png");
    Texture2D mesa2 = LoadTexture("mesa2.png");
    Texture2D mesa3 = LoadTexture("mesa3.png");
    Texture2D mesa4 = LoadTexture("mesa4.png");
    //menu
    Vector2 menuPos = { (float)screenWidth - 799,(float)screenHeight - 449 };
    int frameWidthMe = menuPrincipal.width;
    int frameHeightMe = menuPrincipal.height;
    float scalaMe = 3.5f;
    Rectangle sourceRecMe = { 0.0f,0.0f,(float)frameWidthMe,(float)frameHeightMe };
    Rectangle destRecMe = { menuPos.x,menuPos.y,frameWidthMe * scalaMe + 11, frameHeightMe * scalaMe - 18 };
    Vector2 originMe = { 0.0f,0.0f };
    float rotationMe = 0.0f;
    //fondo
    Vector2 fondoPos = { (float)screenWidth - 799,(float)screenHeight - 449 };
    int frameWidthF = fondo.width;
    int frameHeightF = fondo.height;
    float scalaF = 3.5f;
    Rectangle sourceRecF = { 0.0f,0.0f,(float)frameWidthF,(float)frameHeightF };
    Rectangle destRecF = { fondoPos.x,fondoPos.y,frameWidthF * scalaF + 11, frameHeightF * scalaF - 18 };
    Vector2 originF = { 0.0f,0.0f };
    float rotationF = 0.0f;
    //mesa1
    Vector2 mesa1Pos = { (float)screenWidth - 717,(float)screenHeight - 395 };
    int frameWidthM1 = 47;
    int frameHeightM1 = 40;
    float scalaM1 = 3.0f;
    Rectangle sourceRecM1 = { 0.0f,0.0f,(float)frameWidthM1,(float)frameHeightM1 };
    Rectangle destRecM1 = { mesa1Pos.x,mesa1Pos.y,frameWidthM1 * scalaM1, frameHeightM1 * scalaM1 };
    Vector2 originM1 = { (frameWidthM1 * scalaM1) / 2.0f,(frameHeightM1 * scalaM1) / 2.0f };
    float rotation = 0.0f;
    //mesa2
    Vector2 mesa2Pos = { (float)screenWidth - 717,(float)screenHeight - 150 };
    int frameWidthM2 = 47;
    int frameHeightM2 = 40;
    float scalaM2 = 3.0f;
    Rectangle sourceRecM2 = { 0.0f,0.0f,(float)frameWidthM2,(float)frameHeightM2 };
    Rectangle destRecM2 = { mesa2Pos.x,mesa2Pos.y,frameWidthM2 * scalaM2, frameHeightM2 * scalaM2 };
    Vector2 originM2 = { (frameWidthM2 * scalaM2) / 2.0f,(frameHeightM2 * scalaM2) / 2.0f };
    float rotationM2 = 0.0f;
    //mesa3
    Vector2 mesa3Pos = { (float)screenWidth - 70,(float)screenHeight - 325 };
    int frameWidthM3 = 47;
    int frameHeightM3 = 40;
    float scalaM3 = 3.0f;
    Rectangle sourceRecM3 = { 0.0f,0.0f,(float)frameWidthM3,(float)frameHeightM3 };
    Rectangle destRecM3 = { mesa3Pos.x,mesa3Pos.y,frameWidthM3 * scalaM3, frameHeightM3 * scalaM3 };
    Vector2 originM3 = { (frameWidthM3 * scalaM3) / 2.0f,(frameHeightM3 * scalaM3) / 2.0f };
    float rotationM3 = 0.0f;
    //mesa4
    Vector2 mesa4Pos = { (float)screenWidth - 70,(float)screenHeight - 100 };
    int frameWidthM4 = 47;
    int frameHeightM4 = 40;
    float scalaM4 = 3.0f;
    Rectangle sourceRecM4 = { 0.0f,0.0f,(float)frameWidthM4,(float)frameHeightM4 };
    Rectangle destRecM4 = { mesa4Pos.x,mesa4Pos.y,frameWidthM4 * scalaM4, frameHeightM4 * scalaM4 };
    Vector2 originM4 = { (frameWidthM4 * scalaM4) / 2.0f,(frameHeightM4 * scalaM4) / 2.0f };
    float rotationM4 = 0.0f;

    //----------------------------------------------------------------------------
    Rectangle botonPregunta = { screenWidth - 799,screenHeight - 20,110,40 };
    Rectangle botonRegresoGameplay = { screenWidth - 790, screenHeight - 440,90,40 };
    Rectangle botonInfo = { screenWidth - 790, screenHeight - 50, 85,35 };
    Rectangle cuadroInfo = { screenWidth - 790, screenHeight - 150, 50,50 };

    Rectangle botonResp1 = { screenWidth - 750, screenHeight - 320, 20,20 };
    Rectangle botonResp2 = { screenWidth - 750,screenHeight - 290, 20, 20 };
    Rectangle botonResp3 = { screenWidth - 750, screenHeight - 260, 20, 20 };
    Rectangle botonResp4 = { screenWidth - 750,screenHeight - 230,20,20 };
    Rectangle botonEnviarResp = { screenWidth - 110, screenHeight - 60, 100,50 };
    Color botonColor = BLUE;
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
            DrawTexturePro(menuPrincipal, sourceRecMe, destRecMe, originMe, rotationMe, WHITE);
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

            

            if (IsKeyDown(KEY_RIGHT) && personajePos.x < 799 ) {
                personajePos.x += velocidadBol;
            };
            if (IsKeyDown(KEY_LEFT) && personajePos.x > 4 ) {
                personajePos.x -= velocidadBol;
            };
            if (IsKeyDown(KEY_UP) && personajePos.y > 1) {
                personajePos.y -= velocidadBol;
            };
            if (IsKeyDown(KEY_DOWN) && personajePos.y < 449 ) {
                personajePos.y += velocidadBol; 
            };
            /*Rectangle nextPos;

            // Movimiento hacia la derecha
            nextPos = destRecP;
            nextPos.x += velocidadBol;
            if (IsKeyDown(KEY_RIGHT) && personajePos.x < 799 &&
                !(CheckCollisionRecs(nextPos, destRecM1) ||
                    CheckCollisionRecs(nextPos, destRecM2) ||
                    CheckCollisionRecs(nextPos, destRecM3) ||
                    CheckCollisionRecs(nextPos, destRecM4))) {
                personajePos.x += velocidadBol;
            }

            // Movimiento hacia la izquierda
            nextPos = destRecP;
            nextPos.x -= velocidadBol;
            if (IsKeyDown(KEY_LEFT) && personajePos.x > 4 &&
                !(CheckCollisionRecs(nextPos, destRecM1) ||
                    CheckCollisionRecs(nextPos, destRecM2) ||
                    CheckCollisionRecs(nextPos, destRecM3) ||
                    CheckCollisionRecs(nextPos, destRecM4))) {
                personajePos.x -= velocidadBol;
            }

            // Movimiento hacia arriba
            nextPos = destRecP;
            nextPos.y -= velocidadBol;
            if (IsKeyDown(KEY_UP) && personajePos.y > 1 &&
                !(CheckCollisionRecs(nextPos, destRecM1) ||
                    CheckCollisionRecs(nextPos, destRecM2) ||
                    CheckCollisionRecs(nextPos, destRecM3) ||
                    CheckCollisionRecs(nextPos, destRecM4))) {
                personajePos.y -= velocidadBol;
            }

            // Movimiento hacia abajo
            nextPos = destRecP;
            nextPos.y += velocidadBol;
            if (IsKeyDown(KEY_DOWN) && personajePos.y < 449 &&
                !(CheckCollisionRecs(nextPos, destRecM1) ||
                    CheckCollisionRecs(nextPos, destRecM2) ||
                    CheckCollisionRecs(nextPos, destRecM3) ||
                    CheckCollisionRecs(nextPos, destRecM4))) {
                personajePos.y += velocidadBol;

            }*/
            //if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) currentScreen = ENDING;

            

            break;
        }
        case PREGUNTAS: {
            std::string lin;
            std::ifstream archivo("Preguntas.txt", std::ios::in);
            
                if (!preguntaSeleccionadaFlag) {
                    std::srand(std::time(nullptr));
                    bool preguntaEncontrada;
                    do {
                        preguntaEncontrada = false;
                        // Selecciona una pregunta aleatoria
                        preguntaIndex = std::rand() % listaPreguntas.size();
                        lineaRand = listaPreguntas[preguntaIndex];

                        archivo.clear();
                        archivo.seekg(0, std::ios::beg);

                        while (getline(archivo,lin)) {
                            if (lin == "PREGUNTA: " + lineaRand) {
                                preguntaEncontrada = true;
                                break;
                            }
                        }

                    } while (preguntaEncontrada);
                    preguntaSeleccionadaFlag = true;

                    // Configurar opciones
                    const std::vector<std::string>& opciones = listaOpciones[preguntaIndex];
                    // Asignar opciones a los botones
                    botonResp1.y = 100;
                    botonResp2.y = 160;
                    botonResp3.y = 220;
                    botonResp4.y = 280;
                }
            
                // Manejo de clics en las opciones
                if (!respuestaSeleccionadaFLag) {
                    Vector2 mousePos = GetMousePosition();

                    if (CheckCollisionPointRec(mousePos, botonResp1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        respSelec = 1;
                        letra = 'A';
                        respuestaSeleccionadaFLag = true;
                    }
                    if (CheckCollisionPointRec(mousePos, botonResp2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        respSelec = 2;
                        letra = 'B';
                        respuestaSeleccionadaFLag = true;
                    }
                    if (CheckCollisionPointRec(mousePos, botonResp3) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        respSelec = 3;
                        letra = 'C';
                        respuestaSeleccionadaFLag = true;
                    }
                    if (CheckCollisionPointRec(mousePos, botonResp4) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        respSelec = 4;
                        letra = 'D';
                        respuestaSeleccionadaFLag = true;
                    }
                }
            
            break;
        }
        case CHATBOT: {
            static char text[256] = { 0 }; // Inicializa el texto vacío
            static int textLength = 0;

            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 126) || (key >= 192 && key <= 255)) {
                    if (textLength < sizeof(text) - 1) {
                        text[textLength++] = (char)key;
                        text[textLength] = '\0'; // Aseguramos que el texto esté terminado en nulo
                    }
                }
                key = GetCharPressed(); // Captura el siguiente carácter
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (textLength > 0) {
                    textLength--;
                    text[textLength] = '\0'; // Aseguramos que el texto esté terminado en nulo
                }
            }

            if (IsKeyPressed(KEY_ENTER)) {
                preguntaUsuario = text;
                respuesta = chatBot.obtenerOpcionCorrecta(text);

                textLength = 0; // Limpiar el campo de texto
            }

            DrawRectangle(10, 50, 780, 40, LIGHTGRAY);
            DrawText(text, 20, 55, 20, DARKGRAY);

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
            DrawText("Bienvenidos a todos!!", screenWidth - 540, 170, 30, BLACK);
            DrawText("Presiona Enter para controlar bot", 210, 250, 22, BLACK);
            DrawText("Presiona C para abrir el Chatbot", 204, 360, 25, BLACK);
            {
                int textWidth = MeasureText("Presiona ESC para salir", 30);
                int screenW = GetScreenWidth();
                int screenH = GetScreenHeight();
                DrawText("Presiona ESC para salir", screenW - textWidth - 10, screenH - 40, 30, PINK);
            }
            break;
        case GAMEPLAY:
            // Diseño del juego en si
            
            UpdateMusicStream(musica);
            DrawTexturePro(fondo, sourceRecF, destRecF, originF, rotationF, WHITE);
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


            if (CheckCollisionRecs(destRecP, destRecM1) || CheckCollisionRecs(destRecP, destRecM2) || CheckCollisionRecs(destRecP, destRecM3)
                || CheckCollisionRecs(destRecP, destRecM4)) {
                botonPregunta.x = 800 - 790;
                botonPregunta.y = 450 - 50;
                DrawRectangleRec(botonPregunta, GRAY);
                DrawText("Responder", screenWidth-790,screenHeight-41,20,BLACK);
                if (IsMouseOverRectangle(botonPregunta.x, botonPregunta.y, botonPregunta.width, botonPregunta.height) &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentScreen = PREGUNTAS;
                    preguntaSeleccionadaFlag = false;
                }
            }
            break;
        case PREGUNTAS: {
            static bool mensajeAdvertenciaFlag = false;
            static float tiempoInicioAdvertencia = 0;
            

            // Dibuja la pregunta y las opciones
            DrawText(lineaRand.c_str(), 50, 50, 20, BLACK);
            DrawRectangleRec(botonResp1, respSelec == 1 ? GREEN : BLACK);
            DrawRectangleRec(botonResp2, respSelec == 2 ? GREEN : BLACK);
            DrawRectangleRec(botonResp3, respSelec == 3 ? GREEN : BLACK);
            DrawRectangleRec(botonResp4, respSelec == 4 ? GREEN : BLACK);
            DrawRectangleRec(botonEnviarResp, botonColor);
            DrawText("Enviar", botonEnviarResp.x + 10, botonEnviarResp.y + 10, 20, BLACK);

            // Mostrar opciones
            const std::vector<std::string>& opciones = listaOpciones[preguntaIndex];
            DrawText(opciones[0].c_str(), botonResp1.x + 10, botonResp1.y + 10, 20, BLACK);
            DrawText(opciones[1].c_str(), botonResp2.x + 10, botonResp2.y + 10, 20, BLACK);
            DrawText(opciones[2].c_str(), botonResp3.x + 10, botonResp3.y + 10, 20, BLACK);
            DrawText(opciones[3].c_str(), botonResp4.x + 10, botonResp4.y + 10, 20, BLACK);

            

            // Manejo de clics en el botón Enviar
            if (CheckCollisionPointRec(GetMousePosition(), botonEnviarResp) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (respuestaSeleccionadaFLag) {
                    std::string aux=listaRespuestas[preguntaIndex];
                    respuestaCorrecta = (aux.substr(1) == letra);
                    mostrarResultado = true;
                    tiempoInicio = GetTime(); // Guardar el tiempo en que se muestra el resultado
                    preguntaSeleccionadaFlag = false; // Permite seleccionar una nueva pregunta
                    respuestaSeleccionadaFLag = false; // Permite seleccionar una nueva respuesta
                    respSelec = -1; // Restablecer selección de respuesta
                    if (respuestaCorrecta) {
                        std::fstream archivo("Preguntas.txt", std::ios::in | std::ios::out | std::ios::app);
                        std::string linea;
                        bool lineaEncontrada = false;

                        if (archivo.is_open()) {
                            archivo.seekp(0, std::ios::beg);
                            while (getline(archivo, linea)) {
                                if (linea.find("PREGUNTA: " + lineaRand) != std::string::npos) {
                                    lineaEncontrada = true;
                                    break;
                                }
                            }
                            if (!lineaEncontrada) {
                                archivo.clear();
                                archivo.seekp(0, std::ios::end);
                                archivo << "PREGUNTA: " << lineaRand << "\n";
                                archivo << opciones[0] << "\n";
                                archivo << opciones[1] << "\n";
                                archivo << opciones[2] << "\n";
                                archivo << opciones[3] << "\n";
                                archivo << "RESPUESTA: " << letra << "\n";
                            }
                            archivo.close();

                        }
                    }
                }
                else {
                    if (!mensajeAdvertenciaFlag) {
                        tiempoInicioAdvertencia = GetTime(); // Guardar el tiempo en que se muestra la advertencia
                        mensajeAdvertenciaFlag = true; // Activar la advertencia
                    }

                }
            }

            // Mostrar mensaje de advertencia durante 3 segundos
            if (mensajeAdvertenciaFlag) {
                float tiempoActual = GetTime();
                if (tiempoActual - tiempoInicioAdvertencia <= 3) {
                    DrawText("Seleccione una opcion antes de enviar.", 100, 400, 20, RED);
                }
                else {
                    mensajeAdvertenciaFlag = false; // Desactivar la advertencia después de 3 segundos
                }
            }
            
            // Mostrar mensaje de respuesta durante 3 segundos
            if (mostrarResultado) {
                float tiempoActual = GetTime();
                if (respuestaCorrecta) {
                    DrawText("Respuesta correcta", 100, 400, 20, GREEN);
                    currentScreen = GAMEPLAY;
                }
                else {
                    DrawText("Respuesta incorrecta", 100, 400, 20, RED);
                }

                // Mostrar el resultado durante 3 segundos
                if (tiempoActual - tiempoInicio > 3) {
                    mostrarResultado = false;
                    //currentScreen = GAMEPLAY;
                }
            }

            // Dibuja los botones adicionales
            DrawRectangleRec(botonRegresoGameplay, BLUE);
            DrawText("Volver", botonRegresoGameplay.x + 10, botonRegresoGameplay.y + 10, 20, BLACK);
            //DrawRectangleRec(botonInfo, GREEN);
            //DrawText("Ayuda", botonInfo.x + 10, botonInfo.y + 10, 20, BLACK);

            // Manejo de clics en el botón Volver
            if (CheckCollisionPointRec(GetMousePosition(), botonRegresoGameplay) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                // Cambia al estado GAMEPLAY o el estado que corresponda
                currentScreen = GAMEPLAY;
            }

            // Manejo de clics en el botón Ayuda
            /*if (CheckCollisionPointRec(GetMousePosition(), botonInfo) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                // Mostrar información de ayuda
                // Ejemplo de cómo manejar la ayuda
            }*/
            break;
        }
        case CHATBOT:
            DrawText("Hola, soy WashoBot. Escribe tu pregunta:", 10, 10, 20, DARKGRAY);
            
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
    UnloadTexture(fondo);
    UnloadTexture(menuPrincipal);
    UnloadMusicStream(musica);  
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
