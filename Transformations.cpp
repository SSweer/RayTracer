#include "Transformations.h"

Transformations::Transformations() {
}


Transformations::~Transformations() {
}

Matrix4f Transformations::translationMatrix(float tx, float ty, float tz) {
	Matrix4f m;
	m << 1, 0, 0, tx,
		0, 1, 0, ty,
		0, 0, 1, tz,
		0, 0, 0, 1;

	return m;
}

Matrix4f Transformations::scalarMatrix(float sx, float sy, float sz) {
	Matrix4f m;
	m << sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1;

	return m;
}

Matrix4f Transformations::shearMatrix(float hxy, float hyx, float hxz, float hzx, float hyz, float hzy) {
	Matrix4f m;
	m << 1, hxy, hxz, 0,
		hyx, 1, hyz, 0,
		hzx, hzy, 1, 0,
		0, 0, 0, 1;

	return m;
}

Matrix3f Transformations::rotateXMatrix(float theta) {
	Matrix3f m;
	m << 1, 0, 0,
		0, cos(theta), sin(theta),
		0, sin(theta), cos(theta);

	return m;
}

Matrix3f Transformations::rotateYMatrix(float theta) {
	Matrix3f m;
	m << cos(theta), 0, sin(theta),
		0, 1, 0,
		sin(theta), 0, cos(theta);


	return m;
}

Matrix3f Transformations::rotateZMatrix(float theta) {
	Matrix3f m;
	m << cos(theta), sin(theta), 0,
		sin(theta), cos(theta), 0,
		0, 0, 1;

	return m;
}