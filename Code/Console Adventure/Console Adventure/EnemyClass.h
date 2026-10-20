#include <iostream>
#include "Entity.h"
#pragma once


using namespace std;

class Enemy {
public:
	//Enemy(Entity hello);
	int currentState = 0;
	void toggle() {
		currentState++;
	}

private:
};