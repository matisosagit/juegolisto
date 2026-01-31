#include "Personaje.h"
Personaje::Personaje() {
    // Constructor implementation (if needed)
}

void obtenerPosicion(Personaje& p) {
    return p.posicion;
}

void Personaje::mover(int x, int y) {
    posicion.x += x;
    posicion.y += y;
}

