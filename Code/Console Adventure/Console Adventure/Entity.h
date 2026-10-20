#pragma once

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