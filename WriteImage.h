#pragma once
#include <iostream>
#include <fstream>

#include "Scene.h"
#include "Includes.h"


const class WriteImage {
public:
	WriteImage(Scene&);
	~WriteImage();
	void write(string, int, int);

private:
	Scene& _scene = Scene();
};

