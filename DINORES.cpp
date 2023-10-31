#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define OBSTACLE 'A'
#define PLAYER 'L'
#define GROUND '_'

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool PlayAgain() {
    cout << "¿Quieres jugar de nuevo? (S para jugar de nuevo, cualquier otra tecla para salir): ";
    char choice = _getch();
    return (choice == 'S' || choice == 's');
}

int main() {
    int max_x = 40;
    int max_y = 10;
    int player_x = 10;
    int player_y = max_y - 3;
    int jump = 0;
    int obstacle_x = max_x;
    int score = 0;

    srand(time(NULL));

    bool replay = true;

    while (replay) {
        while (true) {
            system("cls");  // Limpia la pantalla

            // Dibuja el suelo
            for (int i = 0; i < max_x; i++) {
                gotoxy(i, max_y - 3);
                cout << GROUND;
            }

            // Mueve al jugador
            gotoxy(player_x, player_y);
            cout << PLAYER;

            // Mueve el obstáculo
            gotoxy(obstacle_x, max_y - 3);
            cout << OBSTACLE;
            obstacle_x--;

            // Verifica la colisión
            if (player_x == obstacle_x && player_y == max_y - 3) {
                gotoxy(max_x / 2 - 10, max_y / 2);
                cout << "¡Has perdido!";
                _getch();
                break;
            }

            // Incrementa el marcador si se pasa el obstáculo
            if (obstacle_x == 0) {
                score++;
                obstacle_x = max_x;
            }

            // Actualiza el marcador en la pantalla
            gotoxy(0, 0);
            cout << "Score: " << score;

            // Realiza un salto si se presiona la barra espaciadora
            if (_kbhit()) {
                char key = _getch();
                if (key == ' ' && !jump) {
                    jump = 2;
                }
            }

            // Controla el salto
            if (jump) {
                player_y -= 2;  // Salto
                if (player_y <= 0) {
                    jump = 0;
                    player_y = max_y - 3;
                }
            }

            Sleep(100);  // Espera para la próxima iteración
        }

        // Pregunta al usuario si quiere jugar de nuevo
        replay = PlayAgain();

        // Restablece las variables para un nuevo juego si elige jugar de nuevo
        if (replay) {
            player_x = 10;
            player_y = max_y - 3;
            jump = 0;
            obstacle_x = max_x;
            score = 0;
        }
    }

    return 0;
}