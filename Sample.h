#pragma once
#include "Includes.h"

class Sample {
public:
	Sample();
	Sample(int, int);
	~Sample();
	void update(Eigen::Array3f);
	void finalize();

	int x, y;
	Eigen::Array3f color;
};

