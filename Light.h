#pragma once
#include "Includes.h"
#include "Shape.h"
#include "Ray.h"

class Light {
public:
	virtual Eigen::Array3f phongShade(Shape&, const Eigen::Vector3f&, Eigen::Vector3f&) = 0;
	virtual Ray createLightRay(const Eigen::Vector3f&) = 0;

protected:
	Eigen::Vector3f _position;
	Eigen::Array3f _color;
};

