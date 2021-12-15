#include "GameHandler.h"
using namespace std;

GameHandler::GameHandler()
	:player(COORD{ 30, 18 }, ">-0-<")
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			enemies.push_back(GameObject({ (short)(10 + 10 * j + i * 5), (short)(3 + i * 2) }, "[XUX]"));
		}
	}

	field = new char[WIDTH * HEIGHT];
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (x == 0 || x == WIDTH - 1) {
				field[y * WIDTH + x] = '|';
			}
			else if (y == HEIGHT - 1 || y == 1) {
				field[y * WIDTH + x] = '-';
			}
			else
				field[y * WIDTH + x] = ' ';
		}
	}

	for (int i = 0; i < 5; i++) {
		key[i] = 0;
	}

	score = 0;
	speed = 4;
	speedCounter = 0;
	spaceKeyPressed = false;
	enemiesMove = false;
	forceDown = false;
	enemiesDirection = true;
	enemiesDown = false;
	isGameContinue = 'n';
}

void GameHandler::GameTiming() {
	Sleep(50);
	speedCounter++;
	forceDown = (speedCounter >= speed);
}

void GameHandler::drawAll() {
	//board render
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			ScreenBuffer.drawToBackBuffer(x, y, field[y * WIDTH + x]);
		}
	}

	//score render
	char scoreText[20];
	sprintf_s(scoreText, "Score: %d", score);
	ScreenBuffer.drawToBackBuffer(50, 0, scoreText);

	//bullets render
	for (auto i : bullets) {
		ScreenBuffer.drawToBackBuffer(i.getPos().X, i.getPos().Y, i.getImage().c_str());
	}

	//enemies render
	for (auto i : enemies) {
		ScreenBuffer.drawToBackBuffer(i.getPos().X, i.getPos().Y, i.getImage().c_str());
	}

	//player render
	ScreenBuffer.drawToBackBuffer(player.getPos().X, player.getPos().Y, player.getImage().c_str());

	//render to buffer
	ScreenBuffer.Render();
}

void GameHandler::getInput() {
	for (int k = 0; k < 5; k++) {								// R   L   D   U   S
		key[k] = ((1 << 15) & GetAsyncKeyState((unsigned char)("\x27\x25\x28\x26\x20"[k]))) != 0;
	}
}

bool GameHandler::gameLogic() {
	bool isGameOver = false;

	playerLogic();
	if (forceDown) {
		enemiesLogic();
		speedCounter = 0;
	}
	bulletsLogic();

	isGameOver = (score == 8);
	for (auto i : enemies) {
		isGameOver = (i.getPos().Y == 19);
	}

	return isGameOver;
}

void GameHandler::playerLogic() {

	//R
	if (key[0] && player.getPos().X < 54)
		player.setPos(COORD{ player.getPos().X + 1, player.getPos().Y });
	//L
	if (key[1] && player.getPos().X > 1)
		player.setPos(COORD{ player.getPos().X - 1, player.getPos().Y });
	//D
	if (key[2] && player.getPos().Y < 18)
		player.setPos(COORD{ player.getPos().X, player.getPos().Y + 1 });
	//U
	if (key[3] && player.getPos().Y > 2)
		player.setPos(COORD{ player.getPos().X, player.getPos().Y - 1 });
	//S
	if (key[4] && player.getPos().Y > 2) {
		if (!spaceKeyPressed) {
			shoot();
			spaceKeyPressed = true;
		}
	}
	else
		spaceKeyPressed = false;
}

void GameHandler::enemiesLogic() {
	if (enemiesDown) {
		for (auto& i : enemies) {
			i.setPos(COORD{ i.getPos().X, i.getPos().Y + 1 });
		}
		enemiesDown = false;
		return;
	}

	if (enemiesDirection) {
		for (auto i : enemies) {
			if (i.getPos().X < 8)
			{
				enemiesDown = true;
				enemiesDirection = false;
				return;
			}
		}
		for (auto& i : enemies) {
			i.setPos(COORD{ i.getPos().X - 1, i.getPos().Y });
		}
	}
	else {
		for (auto i : enemies) {
			if (i.getPos().X > 47)
			{
				enemiesDown = true;
				enemiesDirection = true;
				return;
			}
		}
		for (auto& i : enemies) {
			i.setPos(COORD{ i.getPos().X + 1, i.getPos().Y });
		}
	}
}

void GameHandler::bulletsLogic() {

	for (int i = 0; i < (int)bullets.size(); i++) {
		for (int j = 0; j < (int)enemies.size(); j++) {
			if (bullets[i].getPos().Y - 1 == enemies[j].getPos().Y && bullets[i].getPos().X >= enemies[j].getPos().X && bullets[i].getPos().X <= enemies[j].getPos().X + 4) {
				bulletsIt = bullets.begin() + i;
				bullets.erase(bulletsIt);
				enemiesIt = enemies.begin() + j;
				enemies.erase(enemiesIt);
				score++;
				i--;
				break;
			}
		}

	}

	bulletsIt = bullets.begin();
	for (int i = 0; i < (int)bullets.size(); i++) {
		if (bullets[i].getPos().Y == 1) {
			bulletsIt = bullets.erase(bulletsIt);
			i--;
		}
		else
			bulletsIt++;
	}

	for (auto& i : bullets) {
		i.setPos(COORD{ i.getPos().X, i.getPos().Y - 1 });
	}
}

void GameHandler::shoot() {
	bullets.push_back(GameObject({ player.getPos().X + 2, player.getPos().Y - 1 }, "!"));
}

char GameHandler::printGameOver() {
	system("cls");
	while (_kbhit()) {
		_getch();
	}
	if (score == 8)
		cout << "YOU WIN!!" << endl;

	else
		cout << "YOU LOSE!!" << endl;
	cout << "Score: " << score << endl;
	cout << "Play Again? (y/n): ";
	cin >> isGameContinue;

	return isGameContinue;
}
