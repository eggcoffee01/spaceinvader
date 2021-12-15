#include <iostream>
#include "GameHandler.h"

int main(void) {
	bool isGameOver = false;
	GameHandler handler;
	char isGameContinue = 'y';
	while (isGameContinue == 'y') {
		while (!isGameOver) {
			//1. Game timing
			handler.GameTiming();

			//2. Get input
			handler.getInput();

			//3. Game logic
			isGameOver = handler.gameLogic();

			//4. Render ouput
			handler.drawAll();
		}
		isGameContinue = handler.printGameOver();	
		if (isGameContinue == 'y') {
			GameHandler temp;
			handler = temp;
			isGameOver = false;
		}
	}
  
	return 0;
}
