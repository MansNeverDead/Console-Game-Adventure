// Console Adventure.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> // Basics
#include <fstream> // To open files
#include <vector> // I believe this is self-explanatory
#include<tuple> // This as well
#include <string> // To make getline() to work

#include "Entity.h"
#include "backgroundFunctions.h"

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

tuple <int, int> playerInput(bool* isAttacking) {
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
    else if (input == 'a') {
        *isAttacking = true;
    }
    return make_tuple(NULL, NULL);
}

void enemiesMOVING(Entity* enemy, Entity oppsArray[7], Entity player, bool spelled) {
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

    if (canMove(directionX, directionY, map) && loopThroughEnemies(oppsArray, directionX, directionY) == -1) {
        enemy->x = directionX; enemy->y = directionY;
    }

}

void spellHitEnemy(Entity enemyArray[7], Entity player) {
    int x = player.x - 1; int y = player.y - 1;

    for (int index = 0; index < 7; index++) {

        if (enemyArray[index].x <= player.x + 1 && enemyArray[index].x >= player.x - 1 && enemyArray[index].y <= player.y + 1 && enemyArray[index].y >= player.y - 1) {
            recieveDamage(&enemyArray[index], player.damage);
            if (enemyArray[index].HP <= 0) {
                enemyArray[index].alive = false;
            }
        }
    }
}

int main() {
    Entity user{ 0, 0, 'H', 1, 1};
    Entity* userPtr = &user;

    Entity enemyArray[7]{
        {0, 0, 'X', 1, 1 },
        {0, 0, 'X', 1, 1 },
        {0, 0, 'X', 1, 1 },
        {0, 0, 'X', 1, 1 },
        {0, 0, 'X', 1, 1 },
        {0, 0, 'X', 1, 1 },
        {0, 0, 'X', 1, 1 } };

    bool isAttacking = false; bool* isAttackingPtr = &isAttacking;
    getMap("Level1", map, userPtr, enemyArray);
    //makeMap(22, 22, map);
    visualiseMap(22, 22, map, user, enemyArray, isAttacking);
    int addX = 0; int addY = 0;
    int tempMouvX; int tempMouvY;
    int atLevel = 1;
    while (true) {
        isAttacking = false;

        tie(addX, addY) = playerInput(isAttackingPtr);
        tempMouvX = user.x + addX;
        tempMouvY = user.y + addY;
        
        
        if (canMove(tempMouvX, tempMouvY, map)) {
            user.x = tempMouvX; user.y = tempMouvY;
        }
        for (int i = 0; i < 7; i++) {
            Entity* opp = &enemyArray[i];
            enemiesMOVING(opp, enemyArray, user, isAttacking);
        }
        if (isAttacking) {
            spellHitEnemy(enemyArray, user);
        }
        beatLevel(tempMouvX, tempMouvY, map, &atLevel, userPtr, enemyArray);

        
        if (touchingEnemy(user, enemyArray)) {
            recieveDamage(userPtr, 1);
            if (user.HP <= 0) {
                deathScreen();
                break;
            }
        }

        visualiseMap(22, 22, map, user, enemyArray, isAttacking);


    }
    
}

