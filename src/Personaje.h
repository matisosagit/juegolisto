#pragma once
#include "raylib.h"

struct Pos { int x{}, y{}; };

struct Player {
    Vector2 pos{0,0};
    float speed = 140.0f;
    float radius = 8.0f;

};

enum class EnemyState { Caminar, Perseguir };

struct Enemy {
    Vector2 pos{0,0};
    float speed = 110.0f;
    float radius = 8.0f;
    EnemyState state = EnemyState::Caminar;

};