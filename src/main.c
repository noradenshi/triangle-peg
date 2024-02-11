#include "peg.h"
#include <raylib.h>

const int width = 800;
const int height = 800;

int main() {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(width, height, "triangle peg");
    SetTraceLogLevel(LOG_DEBUG);

    Texture backgroundTexture = LoadTexture("resources/bg.png");
    initPegs();

    SetTargetFPS(50);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(backgroundTexture, 0, 0, WHITE);
        drawPegs();
        EndDrawing();
    }

    UnloadTexture(backgroundTexture);
    killPegs();
    CloseWindow();
    return 0;
}
