#pragma once
#include <windows.h>
#include <conio.h> 
#include <cwchar>

using namespace std;

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
        *isAttacking = true;
    }
    return make_tuple(NULL, NULL);
}

void transition(Entity* entity, int futureState) {
    if (!(futureState < 5 || futureState > 0)) {
        cout << "the function that called this has a number that is out of bounds";
        abort();
        return;
    }
    entity->currentstate = futureState;
}

void recieveDamage(Entity* victim, int damage) {
    victim->HP = victim->HP - damage;
    if (victim->HP <= 0) {
        transition(victim, dying);
    }
    else {
        transition(victim, moving);
    }
};

void movingEntity(Entity* entity, Entity* player) {
    if (entity == player) {

    }
}