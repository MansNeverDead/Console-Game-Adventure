// Console Adventure.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> // Basics
#include <fstream> // To ppen files
#include <vector> // I believe this is self-explanatory
#include<tuple> // This as well
#include <conio.h> 
#include <windows.h>
#include <cwchar>
#include <string> // To make getline() to work

using namespace std;


/**
Basic Definitions!
- 0 = Basic ground
- 1 = Mountains
- 2 = Rivers
- 3 = Exit
- 4 = Player
- 5 = enemy
*/
int map[22][22];

enum ground {
    basicGround = 0,
    mountain = 1,
    river = 2,
    sortie = 3
};

/**
int x;
int y;
char display = 'X';
int HP;
int damage;
*/
struct Entity {
    int x;
    int y;
    char display = 'H';
    int HP;
    int damage;
};


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

void visualiseMap(int lengthX, int heightY, int map[22][22], Entity user, Entity oppsArray[7]) {
    system("cls");
    cout << "Use Z/Q/S/D to move!" << endl;
    for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < heightY; y++) {
            bool enemyPresent = false;
            for (int i = 0; i < 7; i++) {
                if (x == oppsArray[i].x && y == oppsArray[i].y) {
                    cout << oppsArray[i].display << ' ';
                    enemyPresent = true;
                }
            }

            if (x == user.x && y == user.y) {
                cout << user.display << ' ';
            }
            else if (!enemyPresent) {
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

void enemiesMOVING(Entity* enemy) {
    return;
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

void recieveDamage(Entity* victim, int damage) {
    victim->HP = victim->HP - damage;
};

bool touchingEnemy(Entity user, Entity array[7]) {
    for (int i = 0; i < 6; i++) {
        Entity opp = array[i];
        if (user.x == opp.x && user.y == opp.y) {
            return true;
        }
    }
    return false;
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

bool beatLevel(int x, int y, int map[22][22] ) {
    if (map[x][y] == 3) {
        return true;
    }
    return false;
}

int main() {
    Entity user{ 0, 0, 'H', 1};
    Entity* userPtr = &user;

    Entity firstEnemy{0, 0, 'X', 1, 1};
    Entity secEnemy{0, 0, 'X', 1, 1};
    Entity thEnemy{0, 0, 'X', 1, 1 };
    Entity foEnemy{0, 0, 'X', 1, 1 };
    Entity fiEnemy{0, 0, 'X', 1, 1 };
    Entity sixEnemy{0, 0, 'X', 1, 1 };
    Entity sevEnemy{0, 0, 'X', 1, 1 };

    Entity enemyArray[7]{ firstEnemy, secEnemy, thEnemy, foEnemy, fiEnemy, sixEnemy, sevEnemy };

    getMap("Level3", map, userPtr, enemyArray);
    //makeMap(22, 22, map);
    visualiseMap(22, 22, map, user, enemyArray);
    int addX = 0; int addY = 0;
    int tempMouvX; int tempMouvY;
    int atLevel = 1;
    while (true) {
        tie(addX, addY) = playerInput();
        tempMouvX = user.x + addX;
        tempMouvY = user.y + addY;
        
        if (canMove(tempMouvX, tempMouvY, map)) {
            user.x = tempMouvX; user.y = tempMouvY;
        }
        if (beatLevel(tempMouvX, tempMouvY, map) && atLevel == 1) {
            getMap("Level2", map, userPtr, enemyArray);
            atLevel = 2;
        }
        if (beatLevel(tempMouvX, tempMouvY, map) && atLevel == 2) {
            getMap("Level3", map, userPtr, enemyArray);
            atLevel = 3;
        }
        if (beatLevel(tempMouvX, tempMouvY, map) && atLevel == 3) {
            system("cls");
            cout << "You won...\nYou beat every level..\nYou outbested my every attempt at making you lose...\nYou beated the odds and won.\nSo cheer, celebrate like no tomorrow, for the Winner takes it ALL.";
            break;
        }
        if (touchingEnemy(user, enemyArray)) {
            recieveDamage(userPtr, firstEnemy);
            if (user.HP <= 0) {
                deathScreen();
                break;
            }
        }
        else {
            visualiseMap(22, 22, map, user, enemyArray);
        }


    }
    
    //cout << bs << endl << map[5][5];
}

