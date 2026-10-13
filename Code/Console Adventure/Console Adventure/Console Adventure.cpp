// Console Adventure.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <random>
#include<tuple>
#include <conio.h>

using namespace std;


/** 
Basic Definitions!
- 0 = Basic ground
- 1 = Mountains
- 2 = Rivers
- 3 = Hero/ Player
- 4 = Enemy / The Opps
*/
int map[15][15]; 

enum ground {
    basicGround = 0,
    mountain = 1,
    river = 2
};

char playerDisplay = 'H';
int playerPosX = 7;
int playerPosY = 0;


void makeMap(int lengthX, int heightY, int mapFunction[15][15]) {
    for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < heightY; y++) {
            mapFunction[x][y] = basicGround;
            mapFunction[x][y] = basicGround;
        }
    }
    mapFunction[5][5] = mountain;
    mapFunction[5][6] = mountain;
    mapFunction[5][7] = mountain;


}

char translator(int num) {
    if (num == basicGround) {
        return '.';
    }
    else if (num == mountain) {
        return 'A';
    }
    else if (num == river) {
        return '~';
    }
    else {
        return '.';
    }
}

void visualiseMap(int lengthX, int heightY, int map[15][15]) {
    system("cls");
    cout << "Use Z/Q/S/D to move!" << endl;
    for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < heightY; y++) {
            if (x == playerPosX && y == playerPosY) {
                cout << playerDisplay << ' ';
            }
            else {
                cout << translator(map[x][y]) << ' ';
            }
        }
        cout << endl;
    }
}

int verifyInput() {
    char c = _getch();
    if (c == 'z' || c == 'q' || c == 's' || c == 'd') {
        return c;
    }
    return NULL;
}

tuple <int, int> playerInput() {
    int x = 0; int y = 0;
    char input = verifyInput();
    if (input == 'z') {
        x = x - 1;
        return make_tuple(x, y);
    }
    else if (input == 'q') {
        y = y - 1;
        return make_tuple(x, y);
    }
    else if (input == 's') {
        x = x + 1;
        return make_tuple(x, y);
    }
    else if (input == 'd') {
        y = y + 1;
        return make_tuple(x, y);
    }
    return make_tuple(NULL, NULL);
}

bool canMove(int x, int y, const int map[15][15]) {
    if (map[x][y] == mountain || map[x][y] == river) {
        return false;
    }
    if (x > 15 || x < 0 || y < 0 || y > 15) {
        return false;
    }
    return true;
}

int main() {
    makeMap(15, 15, map);
    visualiseMap(15, 15, map);
    int addX = 0; int addY = 0;
    int tempMouvX; int tempMouvY;

    while (true) {
        tie(addX, addY) = playerInput();
        tempMouvX = playerPosX + addX;
        tempMouvY = playerPosY + addY;
        if (canMove(tempMouvX, tempMouvY, map)) {
            playerPosX = tempMouvX; playerPosY = tempMouvY;
        }
        visualiseMap(15, 15, map);
    }
    
    //cout << bs << endl << map[5][5];
}

