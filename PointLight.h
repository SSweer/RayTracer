#pragma once
#include "Light.h"

class PointLight : public Light {
public:
	PointLight();
	PointLight(Eigen::Vector3f&, Eigen::Array3f&);
	~PointLight();
	Eigen::Array3f phongShade(Shape&, const Eigen::Vector3f&, Eigen::Vector3f&);
	Ray createLightRay(const Eigen::Vector3f&);
};

