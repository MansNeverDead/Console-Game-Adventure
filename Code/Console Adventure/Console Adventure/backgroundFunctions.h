#include "Entity.h"
#include <fstream> // To open files
#include <vector> // I believe this is self-explanatory
#include <string> // To make getline() to work


int level = 0;

enum ground {
    basicGround = 0,
    mountain = 1,
    river = 2,
    sortie = 3
};




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
    else if (num == sortie) {
        return 'E';
    }
    else {
        return '.';
    }
}

int loopThroughEnemies(Entity oppsArray[7], int x, int y) {
    for (int i = 0; i < 7; i++) {
        if (x == oppsArray[i].x && y == oppsArray[i].y && oppsArray[i].alive) {
            return i;
        }
    }
    return -1;
}

void visualiseMap(int lengthX, int heightY, int map[22][22], Entity user, Entity oppsArray[7]) {
    system("cls");
    cout << "Use Z/Q/S/D to move!" << endl;
    for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < heightY; y++) {
            int enemyIndex = loopThroughEnemies(oppsArray, x, y);
            if (user.currentstate == attacked && x <= user.x + 1 && x >= user.x - 1 && y <= user.y + 1 && y >= user.y - 1 && !(x == user.x && y == user.y)) {
                if (map[x][y] == 0) {
                    cout << '*' << ' ';
                }
                else {
                    cout << translator(map[x][y]) << ' ';
                }
            }
            else if (enemyIndex != -1) {
                cout << oppsArray[enemyIndex].display << ' ';
            }
            else if (x == user.x && y == user.y) {
                cout << user.display << ' ';
            }
            else {
                cout << translator(map[x][y]) << ' ';
            }
        }
        cout << endl;
    }
}

void deathScreen() {
    system("cls");
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 100;                  // Height
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi); //essentially saves the values we previously initialised
    CONSOLE_SCREEN_BUFFER_INFOEX csbi{ sizeof csbi }; // Creates the CSBI struct where it saves all the aforemetionned variables

    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); // This is essentially "cout" but for windows

    GetConsoleScreenBufferInfoEx(hOutput, &csbi); // sets the current csbi to the current settings of the console

    csbi.wAttributes = BACKGROUND_RED; //...

    SetConsoleScreenBufferInfoEx(hOutput, &csbi); // updates the console's settings to everything mantionned above
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    printf("YOU DIED!!!!\n");


}

void reviveEnemies(Entity array[7]) {
    for (int i = 0; i < 7; i++) {
        array[i].alive = true;
    }
}

void getMap(string levelName, int grid[22][22], Entity* player, Entity* enemies) {
    string path = levelName + ".txt";
    ifstream file(path);
    if (!file) {
        cerr << "Cannot open file\n";
        return;
    }

    string line;

    int enemiesIndex = 0;

    for (int x = 0; x < 22 && getline(file, line); x++) {
        for (int y = 0; y < 22 && y < (int)line.size(); y++) {
            grid[x][y] = line[y] - '0';
            if (line[y] == '4') {
                player->x = x; player->y = y;
            }
            if (line[y] == '5') {
                enemies[enemiesIndex].x = x; enemies[enemiesIndex].y = y;
                enemiesIndex++;
            }
        }
    }
}

bool canMove(int x, int y, const int map[22][22]) {
    if (map[x][y] == mountain || map[x][y] == river) {
        return false;
    }
    if (x > 21 || x < 0 || y < 0 || y > 21) {
        return false;
    }
    return true;
}

bool touchingEnemy(Entity user, Entity array[7]) {
    for (int i = 0; i < 7; i++) {
        Entity opp = array[i];
        if (user.x == opp.x && user.y == opp.y && opp.alive) {
            return true;
        }
    }
    return false;
}

void beatLevel(int x, int y, int map[22][22], int* level, Entity* userPtr, Entity* enemyArray) {
    if (map[x][y] == 3 && *level == 1) {
        reviveEnemies(enemyArray);
        getMap("Level2", map, userPtr, enemyArray);
        *level = 2;
    }
    else if (map[x][y] == 3 && *level == 2) {
        reviveEnemies(enemyArray);
        getMap("Level3", map, userPtr, enemyArray);
        *level = 3;
    }
    else if (map[x][y] == 3 && *level == 3) {
        system("cls");
        cout << "You won...\nYou beat every level..\nYou outbested my every attempt at making you lose...\nYou beated the odds and won.\nSo cheer, celebrate like no tomorrow, for the Winner takes it ALL.";
        abort();
    }

    return;
}

void spellHitEnemy(Entity enemyArray[7], Entity player) {
    int x = player.x - 1; int y = player.y - 1;
    for (int index = 0; index < 7; index++) {

        if (enemyArray[index].x <= player.x + 1 && enemyArray[index].x >= player.x - 1 && enemyArray[index].y <= player.y + 1 && enemyArray[index].y >= player.y - 1) {
            transition(&enemyArray[index], damaged);
        }
    }
}

void enemiesMoving(Entity* enemy, Entity player) {
    int directionX = enemy->x; int directionY = enemy->y;
    if (player.x < enemy->x) {
        directionX--;
    }
    else if (player.y < enemy->y) {
        directionY--;
    }
    else if (player.x > enemy->x) {
        directionX++;
    }
    else if (player.y > enemy->y) {
        directionY++;
    }

    if (canMove(directionX, directionY, map)) {
        enemy->x = directionX; enemy->y = directionY;
    }
}


/*
void makeMap(int lengthX, int heightY, int mapFunction[22][22]) {
    for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < heightY; y++) {
            mapFunction[x][y] = basicGround;
        }
    }
    mapFunction[5][5] = mountain;
    mapFunction[5][6] = mountain;
    mapFunction[5][7] = mountain;
    mapFunction[5][7] = mountain;
    mapFunction[12][10] = river;
    mapFunction[12][11] = river;
    mapFunction[12][12] = river;
    mapFunction[11][11] = river;
    mapFunction[11][10] = river;
}
*/ // This is an old relic, it was used at the very beginning of the project but not anymore. To show that i have actually done it, i decided to keep it as a comment.

