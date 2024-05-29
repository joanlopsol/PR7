#include "herencias.h"

Personaje::Personaje(int vida, int ataque, string nombre)
    : vida(vida), ataque(ataque), nombre(nombre), posicionX(0), posicionY(0) {}

int Personaje::getVida() const {
    return vida;
}

int Personaje::getAtaque() const {
    return ataque;
}

string Personaje::getNombre() const {
    return nombre;
}

int Personaje::getPosicionX() const {
    return posicionX;
}

int Personaje::getPosicionY() const {
    return posicionY;
}

void Personaje::setPosicion(int x, int y) {
    posicionX = x;
    posicionY = y;
}

void Personaje::mover(int x, int y) {
    posicionX += x;
    posicionY += y;
}

void Personaje::atacar(Personaje& objetivo, int dano) {
    objetivo.recibirAtaque(dano);
}

void Personaje::recibirAtaque(int ataqueRecibido) {
    vida -= ataqueRecibido;
}

bool Personaje::estaVivo() const {
    return vida > 0;
}

Enemigo::Enemigo() : Personaje(50, 5, "Enemigo") {}

EnemigoFinal::EnemigoFinal() : Personaje(150, 20, "Enemigo Final"), superAtaque1(30), superAtaque2(40) {}

void EnemigoFinal::superAtacar(Personaje& objetivo) {
    int ataque = (rand() % 2 == 0) ? superAtaque1 : superAtaque2;
    objetivo.recibirAtaque(ataque);
}
  