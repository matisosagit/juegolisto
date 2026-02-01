#include "raylib.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Personaje.h"
#include <cmath>
#include <algorithm>

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
        for (int x = 0; x < (int)grid[y].size(); x++) {
            char c = grid[y][x];
            Rectangle r{ (float)ox + x * tileSize, (float)oy + y * tileSize,
                        (float)tileSize, (float)tileSize };
            if (c == '#') {
                DrawRectangleRec(r, DARKGRAY);
            } else {
                DrawRectangleRec(r, Color{18,18,18,255});
            }
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

static bool TileBloqueada(const std::vector<std::string>& grid, float x, float y) {
    if (grid.empty()) return true;
    int tx = (int)floorf(x);
    int ty = (int)floorf(y);
    if (ty < 0 || ty >= (int)grid.size()) return true;
    if (tx < 0 || tx >= (int)grid[0].size()) return true;
    return grid[ty][tx] == '#';
}

static bool CircleCollidesMap(const std::vector<std::string>& grid, Vector2 centerPx, float radiusPx, int ox, int oy, int tileSize) {
    if (grid.empty()) return false;
    int minTx = (int)floorf((centerPx.x - radiusPx - ox) / tileSize);
    int maxTx = (int)floorf((centerPx.x + radiusPx - ox) / tileSize);
    int minTy = (int)floorf((centerPx.y - radiusPx - oy) / tileSize);
    int maxTy = (int)floorf((centerPx.y + radiusPx - oy) / tileSize);
    minTx = std::max(minTx, 0);
    maxTx = std::min(maxTx, (int)grid[0].size() - 1);
    minTy = std::max(minTy, 0);
    maxTy = std::min(maxTy, (int)grid.size() - 1);
    for (int ty = minTy; ty <= maxTy; ty++) {
        for (int tx = minTx; tx <= maxTx; tx++) {
            if (grid[ty][tx] != '#') continue;
            Rectangle r{ (float)ox + tx * tileSize, (float)oy + ty * tileSize, (float)tileSize, (float)tileSize };
            if (CheckCollisionCircleRec(centerPx, radiusPx, r)) return true;
        }
    }
    return false;
}


int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Personaje p;
    Vector2 personajePosicion = p.obtenerPosicion();
    InitWindow(screenWidth, screenHeight, "MaskMaze - Preview");
    SetTargetFPS(60);

    Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE };

    auto grid = LoadTextGrid("../../assets/niveles/nivel1.txt");
    bool startSet = false;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);



            const int margin = 30;
    
    int mapH = (int)grid.size();
    int mapW = mapH ?
    (int)grid[0].size() : 0;

    if (mapW == 0 || mapH == 0) {

    }

    // Establecer posición inicial del personaje buscando 'P' en el mapa
    if (!startSet) {
        for (int yy = 0; yy < mapH; yy++) {
            for (int xx = 0; xx < mapW; xx++) {
                if (grid[yy][xx] == 'P') {
                    p.posicion.x = (float)xx;
                    p.posicion.y = (float)yy;
                    startSet = true;
                    break;
                }
            }
            if (startSet) break;
        }
    }

    int tileX = (screenWidth - margin*2) / mapW;
    int tileY = (screenHeight - margin*2) / mapH;
    int tileSize = (tileX < tileY) ? tileX : tileY;

    if (tileSize > 40) tileSize = 40;

    int ox = (screenWidth - mapW * tileSize) / 2;
    int oy = (screenHeight - mapH * tileSize) / 2;

        // Movimiento: usamos colisión circular con resolución por ejes (intentar X, luego Y)
        Vector2 pos = p.obtenerPosicion();
        float paso = 0.2f; // en tiles por frame
        float dx = 0.0f, dy = 0.0f;
        if (IsKeyDown(KEY_D)) dx += paso;
        if (IsKeyDown(KEY_A)) dx -= paso;
        if (IsKeyDown(KEY_S)) dy += paso;
        if (IsKeyDown(KEY_W)) dy -= paso;

        float half = tileSize * 0.5f;
        float radioPx = tileSize * 0.3f;

        if (dx != 0.0f) {
            // centro en pixels si nos movemos en X
            Vector2 centerX = { ox + (pos.x + dx) * tileSize + half, oy + pos.y * tileSize + half };
            if (!CircleCollidesMap(grid, centerX, radioPx, ox, oy, tileSize)) {
                p.mover(dx, 0);
                pos = p.obtenerPosicion();
            }
        }
        if (dy != 0.0f) {
            Vector2 centerY = { ox + pos.x * tileSize + half, oy + (pos.y + dy) * tileSize + half };
            if (!CircleCollidesMap(grid, centerY, radioPx, ox, oy, tileSize)) {
                p.mover(0, dy);
                pos = p.obtenerPosicion();
            }
        }

        if (grid.empty()) {
            DrawText("No se pudo cargar el mapa. Revisa la ruta.", 40, 40, 20, RED);
        } else {
            DrawAsciiMap(grid, tileSize, ox, oy);
            DrawText("Preview del nivel 1", 40, 10, 18, RAYWHITE);
        }

        // Dibujar personaje por encima del mapa (convertir posición de mapa a coordenadas de pantalla)
        personajePosicion = p.obtenerPosicion();
        Vector2 personajeScreen = { ox + personajePosicion.x * tileSize + tileSize * 0.5f,
                                    oy + personajePosicion.y * tileSize + tileSize * 0.5f };
        DrawCircleV(personajeScreen, tileSize * 0.3f, BLUE);

        // Depuración: mostrar posición y tile actual
        int tx = (int)floorf(personajePosicion.x);
        int ty = (int)floorf(personajePosicion.y);
        char tchar = (ty >= 0 && ty < (int)grid.size() && tx >= 0 && tx < (int)grid[0].size()) ? grid[ty][tx] : '?';
        DrawText(TextFormat("pos=%.3f,%.3f  tile=%d,%d char=%c bloqueada=%d", personajePosicion.x, personajePosicion.y, tx, ty, tchar, TileBloqueada(grid, personajePosicion.x, personajePosicion.y)), 40, 40, 18, RAYWHITE);

        EndDrawing();
        
        for (int i = 0; i < (int)grid.size();
        i++) {
            if (grid[i].size() != grid[0].size()) {
                std::cerr << "Fila " << i << "mide " << 
                grid[i].size()
                << " pero deberia medir " <<
                grid[0].size() << "\n";
            }
        }
    }
    CloseWindow();
    return 0;
}