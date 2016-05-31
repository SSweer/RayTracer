#include "Screen.h"

Screen::Screen() {
}

Screen::~Screen() {
}

void Screen::instantiate(int width, int height) {
	_width = width;
	_height = height;
}

int Screen::getWidth() {
	return _width;
}

int Screen::getHeight() {
	return _height;
}