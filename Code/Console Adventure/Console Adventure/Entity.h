#pragma once
#include <conio.h> // used to use _getch 
#include <tuple>

using namespace std;

int map[22][22];

enum StateMachine {
    moving = 0,
    attacking = 1,
    attacked = 2,
    damaged = 3,
    dying = 4,
};

struct Entity {
    int x;
    int y;
    char display = '0';
    int HP;
    int damage;
    bool alive = true;
    int currentstate = moving;
};

struct FSM {
    void (*test)(int, int);
};


Entity user{ 0, 0, 'H', 1, 1 }; Entity* userPtr = &user;

Entity enemyArray[7]{
    {0, 0, 'X', 1, 1 },
    {0, 0, 'X', 1, 1 },
    {0, 0, 'X', 1, 1 },
    {0, 0, 'X', 1, 1 },
    {0, 0, 'X', 1, 1 },
    {0, 0, 'X', 1, 1 },
    {0, 0, 'X', 1, 1 } };

int addX = 0; int addY = 0;
bool isAttacking = false; bool* isAttackingPtr= &isAttacking;

void transition(Entity* entity, int futureState) {

    if (!(futureState < 5 || futureState > 0)) {
        cout << "the function that called this has a number that is out of bounds";
        abort();
        return;
    }
    entity->currentstate = futureState;
}

//Here we declare the functions, however because they are stored inside of backgroundFunctions they won't see it
//Hence we declare them here so the function can still be used while the code will be run inside of backgroundFunctions.
bool canMove(int x, int y, const int map[22][22]);
void enemiesMoving(Entity* enemy, Entity player, Entity enemyArray[7]);
void spellHitEnemy(Entity enemyArray[7], Entity player);
void deathScreen();
void runCurrentState(Entity* entity);

int verifyInput() {
    char c = _getch();
    if (c == 'z' || c == 'q' || c == 's' || c == 'd' || c == 'a') {
        return c;
    }
    return NULL;
}

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
        transition(userPtr, attacked);
        runCurrentState(userPtr);
    }
    return make_tuple(NULL, NULL);
}

void recieveDamage(Entity* victim, int damage) {
    victim->HP = victim->HP - damage;
    if (victim->HP <= 0) {
        transition(victim, dying);
        runCurrentState(victim);
    }
    else {
        transition(victim, moving);
        runCurrentState(victim);
    }
};

void dyingFunc(Entity* entity, Entity* user) {
    if (entity == user) {
        entity->alive = false;
        deathScreen();
    }
    else {
        entity->alive = false; 
    }
}

void movingEntity(Entity* entity, Entity* player) {
    int tempMouvX; int tempMouvY;

    if (entity == player) {
        tie(addX, addY) = playerInput(isAttackingPtr);
        tempMouvX = player->x + addX;
        tempMouvY = player->y + addY;
        if (canMove(tempMouvX, tempMouvY, map)) {
            player->x = tempMouvX; player->y = tempMouvY;
        }
    }
    else {
        for (int i = 0; i < 7; i++) {
            enemiesMoving(&enemyArray[i], user, enemyArray);
        }
    }
}

void runCurrentState(Entity* entity) {
    if (entity->currentstate == moving && userPtr->currentstate != attacked) {
        movingEntity(entity, userPtr);
    }
    else if (entity->currentstate == attacked) {
        spellHitEnemy(enemyArray, user);
    }
    else if (entity->currentstate == damaged) {
        recieveDamage(entity, 1);
    }
    else if (entity->currentstate == dying) {
        dyingFunc(entity, userPtr);
    }
}