#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

// Definiciones de tamaño de pantalla
#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 10

// Definiciones de personajes
#define DINO 'A'
#define OBSTACLE 'X'
#define GROUND '_'

int dinoPosY;
bool isJumping;
int obstaclePos;
int score;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawScreen() {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (y == dinoPosY && x == 10) {
                putchar(DINO);
            } else if (y == SCREEN_HEIGHT - 1) {
                putchar(GROUND);
            } else if (x == obstaclePos) {
                putchar(OBSTACLE);
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}

int main() {
    dinoPosY = SCREEN_HEIGHT - 1;
    isJumping = false;
    obstaclePos = SCREEN_WIDTH - 1;
    score = 0;

    while (1) {
        if (_kbhit()) {
            char key = _getch();
            if (key == ' ' && !isJumping) {
                isJumping = true;
            }
        }

        if (isJumping) {
            dinoPosY--;
            if (dinoPosY == SCREEN_HEIGHT - 5) {
                isJumping = false;
            }
        } else if (dinoPosY < SCREEN_HEIGHT - 1) {
            dinoPosY++;
        }

        obstaclePos--;

        if (obstaclePos == 0) {
            obstaclePos = SCREEN_WIDTH - 1;
            score++;
        }

        if (obstaclePos == 10 && dinoPosY == SCREEN_HEIGHT - 1) {
            break;
        }

        system("cls");
        drawScreen();
        printf("Score: %d", score);

        Sleep(100);
    }

    system("cls");
    printf("Game Over. Your score: %d\n", score);

  return 0;
}
