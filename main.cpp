#include "raylib.h"
#include <cstring>
#include "Preguntas.h"
#include <vector>
#include <string>

//------------------------------------------------------------------------------------
// Program main entry point
typedef enum GameScreen { LOGO = 0, GAMEPLAY, CHATBOT } GameScreen;

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
    Vector2 mesa1Pos = { (float)screenWidth - 750,(float)screenHeight - 450 };
    int frameWidthM1 = mesa1.width;
    int frameHeightM1 = mesa1.height;
    float scalaM1 = 0.2f;
    Rectangle sourceRecM1 = { 0.0f,0.0f,(float)frameWidthM1,(float)frameHeightM1 };
    Rectangle destRecM1 = { mesa1Pos.x,mesa1Pos.y,frameWidthM1 * scalaM1, frameHeightM1 * scalaM1 };
    Vector2 originM1 = { 0.0f,0.0f };
    float rotation = 45.0f;

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
            if (IsKeyDown(KEY_RIGHT)) personajePos.x += velocidadBol;
            if (IsKeyDown(KEY_LEFT)) personajePos.x -= velocidadBol;
            if (IsKeyDown(KEY_UP)) personajePos.y -= velocidadBol;
            if (IsKeyDown(KEY_DOWN)) personajePos.y += velocidadBol;
            //if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) currentScreen = ENDING;

            

            break;
        }
        case CHATBOT: {
            DrawText("Hola, soy Chatbot. Escribe tu pregunta:", 10, 10, 20, DARKGRAY);

            // Campo de texto para la pregunta del usuario
            static char text[256] = { 0 }; // Inicializa el texto vacío
            static int textLength = 0;

            // Captura la entrada del teclado
            int key = GetCharPressed();
            while (key > 0) {
                // Solo capturamos caracteres imprimibles, incluyendo caracteres especiales
                if ((key >= 32) && (key <= 126) || (key >= 192 && key <= 255)) {
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
                int textWidth = MeasureText("Presiona ESC para salir", 30);
                DrawText("Presiona ESC para salir", screenW - textWidth - 10, screenH - 40, 30, PINK);
            }

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
            DrawText("Bienvenido a este mundo!!", 300, 150, 30, BLACK);
            DrawText("Presiona Enter para continuar a la siguiente parte", 200, 200, 30, BLACK);
            DrawText("Presiona C para abrir el Chatbot", 200, 250, 30, BLACK);
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
            DrawText("Aqui va el juego", 0, 0, 30, BLACK);
            // Dibujar el botón de regreso
            {
                int screenW = GetScreenWidth();
                int screenH = GetScreenHeight();
                if (IsMouseOverRectangle(screenW - 130, 10, 120, 40)) {
                    DrawRectangle(screenW - 130, 10, 120, 40, GRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        currentScreen = LOGO;
                    }
                }
                else {
                    DrawRectangle(screenW - 130, 10, 120, 40, LIGHTGRAY);
                }
                DrawText("Volver", screenW - 105, 20, 20, BLACK);
                {
                    int textWidth = MeasureText("Presiona ESC para salir", 30);
                    int screenW = GetScreenWidth();
                    int screenH = GetScreenHeight();
                    DrawText("Presiona ESC para salir", screenW - textWidth - 10, screenH - 40, 30, PINK);
                }
            }
            break;
        case CHATBOT:
            DrawText("Chatbot", 10, 10, 20, DARKGRAY);

            
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
                {
                    int textWidth = MeasureText("Presiona ESC para salir", 30);
                    int screenW = GetScreenWidth();
                    int screenH = GetScreenHeight();
                    DrawText("Presiona ESC para salir", screenW - textWidth - 10, screenH - 40, 30, PINK);
                }
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
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
