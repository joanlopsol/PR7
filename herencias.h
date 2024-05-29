#ifndef HERENCIAS_H
#define HERENCIAS_H

#include <iostream>
#include <string>

using namespace std;

class Personaje {
protected:
    int vida;
    int ataque;
    string nombre;
    int posicionX;
    int posicionY;

public:
    Personaje(int vida = 100, int ataque = 10, string nombre = "Personaje");
    int getVida() const;
    int getAtaque() const;
    string getNombre() const;
    int getPosicionX() const;
    int getPosicionY() const;
    void setPosicion(int x, int y);
    void mover(int x, int y);
    void atacar(Personaje& objetivo, int dano);
    void recibirAtaque(int ataqueRecibido);
    bool estaVivo() const;
};

class Enemigo : public Personaje {
public:
    Enemigo();
};

class EnemigoFinal : public Personaje {
private:
    int superAtaque1;
    int superAtaque2;

public:
    EnemigoFinal();
    void superAtacar(Personaje& objetivo);
};

#endif
