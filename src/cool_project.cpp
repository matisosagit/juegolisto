#include "raylib.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

static std::vector<std::string>
LoadTextGrid(const std::string& path)
{
    std::ifstream f(path);
    std::vector<std::string> grid;
    std::string line;

    if (!f.is_open()) {
        std::cerr << "No se pudo abrir: " << path << "\n";
        return grid;
    }

    while (std::getline(f, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        grid.push_back(line);
    }
    return grid;
}

static void DrawAsciiMap(const
std::vector<std::string>& grid, int tileSize, int ox, int oy) {
    for (int y = 0; y < (int)grid.size(); y++) {
        for (int x = 0; x < (int)grid.size(); x++) {
            char c =grid[y][x];
            Rectangle r{ (float)ox + x * tileSize, (float)oy + y * tileSize,
            (float)tileSize, (float)tileSize };
            if (c == '#')
                DrawRectangleRec(r, DARKGRAY);
            else DrawRectangleRec(r, Color{18,18,18,255});
                DrawRectangleLinesEx(r, 1, Color{35,35,35,255});

            int cx = (int)(r.x + tileSize * 0.5f);
            int cy = (int)(r.y + tileSize * 0.5f);

            if (c == 'P')
            DrawCircle(cx, cy, tileSize * 0.30f, SKYBLUE);
            if (c == 'E')
            DrawCircle(cx, cy, tileSize * 0.30f, RED);
            if (c == 'M')
            DrawCircle(cx, cy, tileSize * 0.26f, GOLD);
            if (c == 'S')
            DrawRectangle((int)r.x+4, (int)r.y+4,tileSize-8, tileSize-8, GREEN);
        }
    }
}

int main()
{
    const int screenWidth = 960;
    const int screenHeight = 540;

    InitWindow(screenWidth, screenHeight, "MaskMaze - Preview");
    SetTargetFPS(60);

    const int tileSize = 24;
    const int ox = 40;
    const int oy = 40;

    auto grid = LoadTextGrid("../../assets/niveles/nivel1.txt");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (grid.empty()) {
            DrawText("No se pudo cargar el mapa. Revisa la ruta.", 40, 40, 20, RED);
        } else {
            DrawAsciiMap(grid, tileSize, ox, oy);
            DrawText("Preview del nivel 1", 40, 10, 18, RAYWHITE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}