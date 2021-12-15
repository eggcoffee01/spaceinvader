#pragma once
#include "GameObject.h"
#include "ScreenBuffer.h"
#include <string>
#include <vector>
#include <iostream>
#include <conio.h>

using namespace std;


class GameHandler {
private:
	char* field;
	bool key[5];
	bool spaceKeyPressed;
	bool enemiesMove;
	bool forceDown;
	bool enemiesDirection;
	bool enemiesDown;
	char isGameContinue;
	int speedCounter;
	int speed;
	int score;
	ScreenBuffer ScreenBuffer;
	GameObject player;
	vector<GameObject> enemies;
	vector<GameObject> bullets;
	vector<GameObject>::iterator bulletsIt;
	vector<GameObject>::iterator enemiesIt;

public:
	GameHandler();
	void GameTiming();
	void drawAll();
	void getInput();
	bool gameLogic();
	void playerLogic();
	void enemiesLogic();
	void bulletsLogic();
	void shoot();
	char printGameOver();

};
