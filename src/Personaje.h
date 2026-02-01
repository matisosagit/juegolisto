#pragma once
#include "raylib.h"


struct Personaje {
    Personaje();
    Vector2 posicion{1,1};
    float speed = 140.0f;
    float radius = 8.0f;
    Vector2 obtenerPosicion() const;
    void mover(float dx, float dy);
};

struct Player {
    Vector2 pos{1,1};
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