// Console Adventure.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <random>
#include <conio.h>

using namespace std;

//char c = _getch();
char map[15][15];

int playerPosX = 7;
int playerPosY = 0;

void makeMap(int lengthX, int heightY, char mapFunction[15][15]) {
    for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < heightY; y++) {
            mapFunction[x][y] = '.';
            mapFunction[x][y] = '.';
        }
    }
}

void visualiseMap(int lengthX, int heightY, char map[15][15]) {
    system("cls");
    cout << "Use Z/Q/S/D to move!" << endl;
    for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < heightY; y++) {
            cout << map[x][y] << ' ';
        }
        cout << endl;
    }
}

char verifyInput() {
    char c = _getch();
    if (c == 'z' || c == 'q' || c == 's' || c == 'd') {
        return c;
    }
    return NULL;
}

void movePlayer(int xMap,int yMap, char map[15][15],int* x, int* y) {
    //This is the Player's current position
    char input = verifyInput();
    if (input == 'z') {
        *x = *x - 1;
        if (*x < 0) {
            *x = *x + 1;
            return;
        }
        map[*x+1][*y] = '.';
        map[*x][*y] = 'H'; 
    }
    else if (input == 'q') {
        map[*x][*y] = '.';
        *y = *y - 1;
        map[*x][*y] = 'H';
    }
    else if (input == 's') {
        map[*x][*y] = '.';
        *x = *x + 1;
        map[*x][*y] = 'H';
    }
    else if (input == 'd') {
        map[*x][*y] = '.';
        *y = *y + 1;
        map[*x][*y] = 'H';
    }
    
}

int main() {
    makeMap(15, 15, map);
    map[7][0] = 'H';
    visualiseMap(15, 15, map);
    int* playerPosXPtr = &playerPosX;
    int* playerPosYPtr = &playerPosY;
    while (true) {
        movePlayer(15, 15, map, playerPosXPtr, playerPosYPtr);


        visualiseMap(15, 15, map);
    }
    
    //cout << bs << endl << map[5][5];
}

