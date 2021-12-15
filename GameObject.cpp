#include "GameObject.h"

GameObject::GameObject() {
	pos = { 0, 0 };
	image = "";
}

GameObject::GameObject(COORD pos, string image) {
	this->pos = pos;
	this->image = image;
}

void GameObject::setPos(COORD pos) {
	this->pos = pos;
}

COORD GameObject::getPos() const{
	return pos;
}

string GameObject::getImage() const {
	return image;
}
