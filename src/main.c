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
        switch (GetKeyPressed()) {
        case KEY_R:
            killPegs();
            initPegs();
            break;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(backgroundTexture, -backgroundTexture.width / 4, 0, WHITE);
        drawPegs();
        EndDrawing();
    }

    UnloadTexture(backgroundTexture);
    killPegs();
    CloseWindow();
    return 0;
}
