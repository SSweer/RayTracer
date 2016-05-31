#include "Sample.h"

Sample::Sample() {
	color = BLACK;
}

Sample::Sample(int x_, int y_) {
	x = x_;
	y = y_;
	color = BLACK;
}

Sample::~Sample() {
}

void Sample::update(Eigen::Array3f c) {
	color += c;
}

void Sample::finalize() {
	color(0) = fminf(color(0), 1);
	color(1) = fminf(color(1), 1);
	color(2) = fminf(color(2), 1);
}

