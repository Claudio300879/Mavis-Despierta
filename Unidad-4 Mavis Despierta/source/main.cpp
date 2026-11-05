#include "raylib.h"

int main() {
    //  Inicialización de ventana 
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Mavis Despierta");

    //  Inicialización de sistema de audio

    InitAudioDevice();

    // Carga de recursos 
    Texture2D mavisSprite = LoadTexture("resources/logo.png");
    Sound stepSound = LoadSound("resources/caminata.wav");
    Sound coordSound = LoadSound("resources/coordenadas.wav");
    Sound jumpSound = LoadSound("resources/salto.mp3");
    Sound msgSound = LoadSound("resources/sistema.wav");

    // Variables de estado desde donde parte Mavis
    Vector2 position = { 400.0f, 400.0f }; // Posición inicial en el suelo (Y = 400)
    float speed = 4.0f;

    // Variables para la física de salto
    bool isJumping = false;
    float verticalVelocity = 0.0f;
    float gravity = 0.5f;
    float groundLevel = 400.0f;

    // Estados iniciales ocultos 
    bool showSystemMessage = false;
    bool showCoordinates = false;
    Color bgColor = RAYWHITE;

    SetTargetFPS(60);

    // Bucle principal del juego
    while (!WindowShouldClose()) {

        //  GESTIÓN DE ENTRADAS (INPUT Y AUDIO) 

        // Movimiento continuo sobre el eje x
        bool isMoving = false;

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            position.x -= speed;
            isMoving = true;
        }
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            position.x += speed;
            isMoving = true;
        }

        
        /*Usamos StopSound que forma parte de la biblioteca oficial de funciones de audio de Raylib, el cual 
        en este caso nos permite reproducir pasos al moverse o cortar el sonido inmediatamente al detenerse        
        */ 
        if (isMoving) {
            if (!IsSoundPlaying(stepSound)) {
                PlaySound(stepSound);
            }
        }
        else {
            if (IsSoundPlaying(stepSound)) {
                StopSound(stepSound);
            }
        }

        //  Salto con la Barra Espaciadora y sonido de salto
        if (IsKeyPressed(KEY_SPACE) && !isJumping) {
            verticalVelocity = -10.0f;
            isJumping = true;
            PlaySound(jumpSound);
        }

        if (isJumping) {
            position.y += verticalVelocity;
            verticalVelocity += gravity;

            if (position.y >= groundLevel) {
                position.y = groundLevel;
                isJumping = false;
                verticalVelocity = 0.0f;
            }
        }

        // Reiniciar posición con la tecla R
        if (IsKeyPressed(KEY_R)) {
            position = { 400.0f, groundLevel };
            isJumping = false;
            verticalVelocity = 0.0f;
        }

        // Mostrar/ocultar mensaje con la tecla M y sonido de sistema
        if (IsKeyPressed(KEY_M)) {
            showSystemMessage = !showSystemMessage;
            PlaySound(msgSound);
        }

        // Mostrar/ocultar coordenadas con la tecla C y sonido de coordenadas
        if (IsKeyPressed(KEY_C)) {
            showCoordinates = !showCoordinates;
            PlaySound(coordSound);
        }

        // Detección de clics del mouse DIRECTAMENTE sobre Mavis para cambiar el fondo
        Vector2 mousePos = GetMousePosition();
        Rectangle mavisRect = { position.x, position.y, (float)mavisSprite.width, (float)mavisSprite.height };

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(mousePos, mavisRect)) {
                if (bgColor.r == RAYWHITE.r) {
                    bgColor = LIGHTGRAY;
                }
                else {
                    bgColor = RAYWHITE;
                }
            }
        }

        // RENDERIZADO Y DIBUJADO 
        BeginDrawing();
        ClearBackground(bgColor);

        // Dibujar al personaje 
        DrawTexture(mavisSprite, (int)position.x, (int)position.y, WHITE);
        DrawText("Mavis", (int)position.x, (int)position.y - 20, 12, DARKGRAY);

        // Coordenadas en pantalla (Se activan con la tecla C)
        if (showCoordinates) {
            DrawText(TextFormat("Coordenadas - X: %.2f | Y: %.2f", position.x, position.y), 20, 20, 16, GRAY);
        }

        // Mensaje del sistema (Se activa con la tecla M)
        if (showSystemMessage) {
            DrawText("[SISTEMA]: Haz clic directamente sobre Mavis para cambiar el entorno.", 20, 50, 18, DARKGREEN);
        }

        // Panel de instrucciones inferior
        DrawText("Controles: A/D (Mover) | Espacio (Salto) | R (Reiniciar) | C (Coordenadas) | M (Mensaje)", 10, 560, 13, DARKGRAY);

        EndDrawing();
    }

    // Liberación segura de recursos y cierre del sistema de audio
    UnloadTexture(mavisSprite);
    UnloadSound(stepSound);
    UnloadSound(coordSound);
    UnloadSound(jumpSound);
    UnloadSound(msgSound);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}