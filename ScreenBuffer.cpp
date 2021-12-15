#include "ScreenBuffer.h"
#include <Windows.h>
#include <iostream>

using namespace std;

ScreenBuffer::ScreenBuffer() {

	system("cls");
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			front_buffer[y][x] = 0;
			back_buffer[y][x] = 0;
		}
	}


	CONSOLE_CURSOR_INFO cur_info;
	cur_info.dwSize = 1;
	cur_info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);
}

void ScreenBuffer::Render() {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (front_buffer[y][x] != back_buffer[y][x]) {
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)x, (short)y });
				if (back_buffer[y][x] == 0) {
					cout << ' ';
				}
				else {
					cout << back_buffer[y][x];
				}
			}
		}
	}

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			front_buffer[y][x] = back_buffer[y][x];
			back_buffer[y][x] = 0;
		}
	}
}

void ScreenBuffer::drawToBackBuffer(const int x, const int y, const char image){
	back_buffer[y][x] = image;
}

void ScreenBuffer::drawToBackBuffer(const int x, const int y, const char *image) {
	for (int i = 0; image[i] != NULL; i++) {
		back_buffer[y][x + i] = image[i];
	}
}
