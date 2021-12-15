#pragma once
#include <string>
#include <Windows.h>
using namespace std;

class GameObject {
private:
	COORD pos;
	string image;
public:
	GameObject();
	GameObject(COORD pos, string image);
	void setPos(COORD pos);
	COORD getPos()const;
	string getImage()const;
};
