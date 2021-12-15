#pragma once
#define WIDTH 60
#define HEIGHT 20

class ScreenBuffer {
private:
	char front_buffer[HEIGHT][WIDTH];
	char back_buffer[HEIGHT][WIDTH];
public:
	ScreenBuffer();
	void Render();
	void drawToBackBuffer(const int x, const int y, const char image);
	void drawToBackBuffer(const int x, const int y, const char *image);
};
