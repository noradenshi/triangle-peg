#include "peg.h"
#include "utils.h"
#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>

const int pegLines = 5;
const int pegSize = 15;
const Vector2 pegStart = {400, 200};
const int pegSpacing = 80;
const int pegRadius = 30;
int pegSelectedId = -1;

const Color triangleMainColor = {0x88, 0x6c, 0x52, 255};
const Color triangleAccentColor = {0x45, 0x3c, 0x39, 255};

struct Peg {
    bool isOccupied;
    Color color;
    Vector2 position;
    int8_t row;
    int8_t col;
    int8_t id;
} *pegs;

int pegFindId(const int row, const int col) {
    if (row < 0 || col < 0 || row > pegLines || col > row)
        return -1;

    int offset = 0;
    for (int i = row; i > 0; i--)
        offset += i;

    return offset + col;
}

void initPegs() {
    pegs = malloc(sizeof(struct Peg) * pegSize);

    int id;
    for (int row = 0; row < pegLines; row++) {
        for (int col = 0; col < row + 1; col++) {
            id = pegFindId(row, col);
            pegs[id].isOccupied = true;
            pegs[id].color =
                (Color){100 + id * 10, 200 - col * 10, 180 - row * 10, 255};
            pegs[id].position =
                (Vector2){pegStart.x + (col - (row + 1.f) / 2) * pegSpacing,
                          pegStart.y + pegSpacing * row};
            pegs[id].row = row;
            pegs[id].col = col;
            pegs[id].id = id;
        }
    }
    pegs[0].isOccupied = false;
}

void killPegs() { free(pegs); }

Color pegGetActionColor(struct Peg peg) {
    if (!peg.isOccupied)
        return DARKGRAY;
    if (pegSelectedId == peg.id)
        return (Color){peg.color.r - 40, peg.color.g - 40, peg.color.b - 40,
                       255};
    return peg.color;
}

void pegCheckForMousePress(int id) {
    if (IsMouseButtonPressed(0)) {
        if (pegs[id].isOccupied) {
            pegSelectedId = id;
            return;
        }
        if (pegSelectedId == -1)
            return;

        const int row_diff = pegs[pegSelectedId].row - pegs[id].row;
        const int col_diff = pegs[pegSelectedId].col - pegs[id].col;
        if (abs(row_diff) == 2 || abs(col_diff) == 2) {
            const int midId = pegFindId(pegs[id].row + row_diff / 2,
                                        pegs[id].col + col_diff / 2);
            if (pegs[midId].isOccupied) {
                pegs[midId].isOccupied = false;
                pegs[pegSelectedId].isOccupied = false;
                pegs[id].isOccupied = true;
                pegs[id].color = pegs[pegSelectedId].color;
                pegSelectedId = -1;
            }
        }
    }
}

void drawPegs() {
    DrawTriangle((Vector2){pegs[0].position.x, pegs[0].position.y - 140},
                 (Vector2){pegs[10].position.x - 120, pegs[10].position.y + 75},
                 (Vector2){pegs[14].position.x + 120, pegs[14].position.y + 75},
                 triangleAccentColor);
    DrawTriangle((Vector2){pegs[0].position.x, pegs[0].position.y - 100},
                 (Vector2){pegs[10].position.x - 80, pegs[10].position.y + 50},
                 (Vector2){pegs[14].position.x + 80, pegs[14].position.y + 50},
                 triangleMainColor);
    DrawTriangleLines(pegs[0].position, pegs[10].position, pegs[14].position,
                      DARKGRAY);
    DrawLineV(pegs[1].position, pegs[13].position, DARKGRAY);
    DrawLineV(pegs[3].position, pegs[12].position, DARKGRAY);
    DrawLineV(pegs[2].position, pegs[11].position, DARKGRAY);
    DrawLineV(pegs[5].position, pegs[12].position, DARKGRAY);

    for (int i = 0; i < pegSize; i++) {
        if (CheckCollisionPointCircle(GetMousePosition(), pegs[i].position,
                                      pegRadius)) {
            DrawCircleV(pegs[i].position, pegRadius + 5, triangleAccentColor);
            pegCheckForMousePress(i);
        }
        if (pegSelectedId == i)
            DrawCircleV(pegs[i].position, pegRadius + 2, triangleAccentColor);
        DrawCircleV(pegs[i].position, pegRadius, pegGetActionColor(pegs[i]));

        //        char str[4] = "0";
        //        strnumber(str, i);
        //        DrawText(str, pegs[i].position.x, pegs[i].position.y,
        //        pegRadius, WHITE);
    }

    char selStr[] = "selected:   ";
    strnumber(&selStr[10], pegSelectedId);
    DrawText(selStr, 0, 0, 20, WHITE);
}
