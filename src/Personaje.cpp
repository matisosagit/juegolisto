#include "Personaje.h"

Personaje::Personaje() = default;

Vector2 Personaje::obtenerPosicion() const {
    return posicion;
}

void Personaje::mover(float dx, float dy) {
    posicion.x += dx;
    posicion.y += dy;
}