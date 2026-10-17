#include "raylib.h"

int main(void) {
    // Ventana con resolución 1024x768
    const int anchoVentana = 1024;
    const int altoVentana = 768;
    InitWindow(anchoVentana, altoVentana, "Sprites en Accion");

    // Carga de textura 
    Texture2D texturaBase = LoadTexture("resources/logo.png");

    // Filtro bilineal 
    //SetTextureFilter(texturaBase, TEXTURE_FILTER_POINT); sin filtro bilineal la imagen se veria pixelada
    SetTextureFilter(texturaBase, TEXTURE_FILTER_BILINEAR);

    // Sprites distintos con la misma textura pero con diferentes propiedades
    // Sprite 1 
    Vector2 posSprite1 = { 200.0f, 300.0f };
    float escalaSprite1 = 2.0f;       // Agrandado al doble
    Color colorSprite1 = RED;         // color rojo

    // Sprite 2 
    Vector2 posSprite2 = { 600.0f, 300.0f };
    float escalaSprite2 = 1.0f;       // Tamaño original
    Color colorSprite2 = WHITE;       // Color original

    // Movimiento e interacción
    float velocidadMovimiento = 200.0f;
    bool modoIntercambio = false;     // Bandera 

    SetTargetFPS(60);//Frame por segundo

    // Bucle principal (Game Loop)
    while (!WindowShouldClose()) {

     
        float deltaTime = GetFrameTime();

        // Movimiento controlado por teclado 
        if (IsKeyDown(KEY_RIGHT)) posSprite1.x += velocidadMovimiento * deltaTime;
        if (IsKeyDown(KEY_LEFT))  posSprite1.x -= velocidadMovimiento * deltaTime;
        if (IsKeyDown(KEY_DOWN))  posSprite1.y += velocidadMovimiento * deltaTime;
        if (IsKeyDown(KEY_UP))    posSprite1.y -= velocidadMovimiento * deltaTime;

        // Interacción al presionar la barra espaciadora se invierten las propiedades y se activa la "bandera"
        if (IsKeyPressed(KEY_SPACE)) {
            modoIntercambio = !modoIntercambio; // Cambia el estado de falso a verdadero y viceversa
        }

        // Cambio de estilo visual
        if (modoIntercambio) {
            escalaSprite1 = 1.0f;
            colorSprite1 = BLUE;
            escalaSprite2 = 2.5f;
            colorSprite2 = GREEN;
        }
        else {
            escalaSprite1 = 2.0f;
            colorSprite1 = RED;
            escalaSprite2 = 1.0f;
            colorSprite2 = WHITE;
        }

        // RENDERIZADO 
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Título superior e instrucciones
        DrawText("Sprites en Accion", 20, 20, 20, DARKGRAY);
        DrawText("Usa las Flechas del teclado para moverte", 20, 50, 18, DARKGRAY);
        DrawText("Presiona [ESPACIO], para ver el efecto", 20, 75, 18, DARKGRAY);

        // Dibujamos 2 sprites
        DrawTextureEx(texturaBase, posSprite1, 0.0f, escalaSprite1, colorSprite1);
        DrawTextureEx(texturaBase, posSprite2, 0.0f, escalaSprite2, colorSprite2);

        // Propiedades de Cada Sprite
        DrawText(TextFormat("Sprite 1 -> Pos: (%.1f, %.1f) | Escala: %.1f", posSprite1.x, posSprite1.y, escalaSprite1), 20, 650, 18, BLACK);
        DrawText(TextFormat("Sprite 2 -> Pos: (%.1f, %.1f) | Escala: %.1f", posSprite2.x, posSprite2.y, escalaSprite2), 20, 680, 18, BLACK);
        DrawText(TextFormat("Modo Swap Visual (Espacio): %s", modoIntercambio ? "ACTIVADO" : "NORMAL"), 20, 710, 18, modoIntercambio ? DARKGREEN : DARKBLUE);

        EndDrawing();
    }

    // Liberación de recursos ocupados en memoria
    UnloadTexture(texturaBase);
    CloseWindow();

    return 0;
}