#pragma once

const class Screen {
public:
	Screen();
	~Screen();
	void instantiate(int, int);
	int getWidth();
	int getHeight();

private:
	int _width;
	int _height;
};

