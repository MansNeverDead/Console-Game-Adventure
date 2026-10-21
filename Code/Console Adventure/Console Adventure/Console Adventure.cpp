// Console Adventure.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> // Basics
#include "Entity.h"
#include "backgroundFunctions.h"

int main() {

    getMap("Level1", map, userPtr, enemyArray);
    //makeMap(22, 22, map);
    visualiseMap(22, 22, map, user, enemyArray);

    int atLevel = 1;
    while (true) {
        transition(userPtr, moving);

        runCurrentState(userPtr);
        runCurrentState(enemyArray);

        beatLevel(tempMouvX, tempMouvY, map, &atLevel, userPtr, enemyArray);


        if (touchingEnemy(user, enemyArray)) {
            transition(userPtr, damaged);
            runCurrentState(userPtr);
        }


        visualiseMap(22, 22, map, user, enemyArray);

    }
    
}

