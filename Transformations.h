#pragma once
#include "Includes.h"

using namespace Eigen;

class Transformations {
public:
	Transformations();
	~Transformations();

	Matrix4f translationMatrix(float, float, float);
	Matrix4f scalarMatrix(float, float, float);
	Matrix4f shearMatrix(float, float, float, float, float, float);

	Matrix3f rotateXMatrix(float);
	Matrix3f rotateYMatrix(float);
	Matrix3f rotateZMatrix(float);
};