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

bool canMove(int x, int y, const int map[22][22]) {
    if (map[x][y] == mountain || map[x][y] == river) {
        return false;
    }
    if (x > 22 || x < 0 || y < 0 || y > 22) {
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
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    CONSOLE_SCREEN_BUFFER_INFOEX csbi{ sizeof csbi };

    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfoEx(hOutput, &csbi);

    csbi.wAttributes = BACKGROUND_RED;

    SetConsoleScreenBufferInfoEx(hOutput, &csbi);
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    printf("YOU DIED!!!!\n");


}

void recieveDamage(Entity* user, Entity opps) {
    user->HP = user->HP - opps.damage;
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

void getMap(string levelName, int grid[22][22]) {
    string path = levelName + ".txt";
    ifstream file(path);
    if (!file) {
        cerr << "Cannot open file\n";
        return;
    }

    //int grid[22][22] = { 0 };
    string line;

    int x = 0;
    while (x < 22 && getline(file, line)) {
        for (int y = 0; y < 22 && y < (int)line.size(); y++) {
            if (line[y] >= '0' && line[y] <= '9') {
                grid[x][y] = line[y] - '0';
            }
        }
        x++;
    }

}

int main() {
    Entity user{ 0, 0, 'H', 1};
    Entity* userPtr = &user;

    Entity firstEnemy{12, 20, 'X', 1, 1};
    Entity secEnemy{10, 10, 'X', 1, 1};
    Entity thEnemy{9, 13, 'X', 1, 1 };
    Entity foEnemy{7, 7, 'X', 1, 1 };
    Entity fiEnemy{3, 2, 'X', 1, 1 };
    Entity sixEnemy{7, 6, 'X', 1, 1 };
    Entity sevEnemy{20, 20, 'X', 1, 1 };

    Entity enemyArray[7]{ firstEnemy, secEnemy, thEnemy, foEnemy, fiEnemy, sixEnemy, sevEnemy };
    getMap("Level1", map);
    //makeMap(22, 22, map);
    visualiseMap(22, 22, map, user, enemyArray);
    int addX = 0; int addY = 0;
    int tempMouvX; int tempMouvY;
    while (true) {
        tie(addX, addY) = playerInput();
        tempMouvX = user.x + addX;
        tempMouvY = user.y + addY;
        if (canMove(tempMouvX, tempMouvY, map)) {
            user.x = tempMouvX; user.y = tempMouvY;

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

