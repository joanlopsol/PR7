#include <iostream>
#include "herencias.h"
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

const int TAMANO = 10;
char mapa[TAMANO][TAMANO];

void inicializarMapa() {
    for (int i = 0; i < TAMANO; ++i) {
        for (int j = 0; j < TAMANO; ++j) {
            mapa[i][j] = '.';
        }
    }
}

void mostrarMapa() {
    system("cls");
    for (int i = 0; i < TAMANO; ++i) {
        for (int j = 0; j < TAMANO; ++j) {
            if (mapa[i][j] == 'J') {
                cout << "\033[1;32m" << mapa[i][j] << "\033[0m" << " ";
            }
            else if (mapa[i][j] == 'E') {
                cout << "\033[1;31m" << mapa[i][j] << "\033[0m" << " ";
            }
            else {
                cout << mapa[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void actualizarMapa(Personaje& jugador, Enemigo enemigos[], int numEnemigos) {
    inicializarMapa();
    mapa[jugador.getPosicionX()][jugador.getPosicionY()] = 'J';
    for (int i = 0; i < numEnemigos; ++i) {
        if (enemigos[i].estaVivo()) {
            mapa[enemigos[i].getPosicionX()][enemigos[i].getPosicionY()] = 'E';
        }
    }
}

void combate(Personaje& jugador, Personaje& enemigo, int& balas) {
    char opcion;
    while (jugador.estaVivo() && enemigo.estaVivo()) {
        cout << "Elige una accion:\n";
        cout << "1. Punetazo\n";
        cout << "2. Bala (te quedan " << balas << ")\n";
        cin >> opcion;
        if (opcion == '1') {
            jugador.atacar(enemigo, jugador.getAtaque());
        }
        else if (opcion == '2' && balas > 0) {
            enemigo.recibirAtaque(100);
            --balas;
        }
        else {
            cout << "Opcion no valida.\n";
            continue;
        }
        if (enemigo.estaVivo()) {
            enemigo.atacar(jugador, enemigo.getAtaque());
        }
        cout << "Vida del jugador: " << jugador.getVida() << endl;
        cout << "Vida del enemigo: " << enemigo.getVida() << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Personaje jugador(100, 10, "Jugador");
    jugador.setPosicion(0, 0);

    const int numEnemigos = 3;
    Enemigo enemigos[numEnemigos];
    for (int i = 0; i < numEnemigos; ++i) {
        int x = rand() % TAMANO;
        int y = rand() % TAMANO;
        enemigos[i].setPosicion(x, y);
    }

    EnemigoFinal enemigoFinal;
    enemigoFinal.setPosicion(TAMANO - 1, rand() % TAMANO);

    int balas = 4;
    while (jugador.estaVivo()) {
        actualizarMapa(jugador, enemigos, numEnemigos);
        mostrarMapa();

        if (jugador.getPosicionX() == enemigoFinal.getPosicionX() && jugador.getPosicionY() == enemigoFinal.getPosicionY()) {
            cout << "Has encontrado al Enemigo Final!\n";
            combate(jugador, enemigoFinal, balas);
            if (jugador.estaVivo()) {
                cout << "Has ganado el juego!\n";
            }
            else {
                cout << "Has perdido el juego.\n";
            }
            break;
        }

        for (int i = 0; i < numEnemigos; ++i) {
            if (jugador.getPosicionX() == enemigos[i].getPosicionX() && jugador.getPosicionY() == enemigos[i].getPosicionY() && enemigos[i].estaVivo()) {
                cout << "Te has encontrado con un enemigo!\n";
                combate(jugador, enemigos[i], balas);
                if (!jugador.estaVivo()) {
                    cout << "Has perdido el juego.\n";
                    return 0;
                }
            }
        }

        cout << "Muevete (w/a/s/d): ";
        char movimiento;
        movimiento = _getch();
        switch (movimiento) {
        case 'w':
            if (jugador.getPosicionX() > 0)
                jugador.mover(-1, 0);
            break;
        case 's':
            if (jugador.getPosicionX() < TAMANO - 1)
                jugador.mover(1, 0);
            break;
        case 'a':
            if (jugador.getPosicionY() > 0)
                jugador.mover(0, -1);
            break;
        case 'd':
            if (jugador.getPosicionY() < TAMANO - 1)
                jugador.mover(0, 1);
            break;
        default:
            cout << "Movimiento no valido.\n";
            break;
        }
    }

    return 0;
}
