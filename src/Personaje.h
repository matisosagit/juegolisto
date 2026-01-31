#include "raylib.h"

class Personaje{
public:
    Personaje();
    void mover(int x, int y);
    Vector2 obtenerPosicion(Personaje& p) {
    }
private:
    Vector2 posicion = {0, 0};
}