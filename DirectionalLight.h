#pragma once
#include "Light.h"

class DirectionalLight : public Light {
public:
	DirectionalLight();
	DirectionalLight(Eigen::Vector3f&, Eigen::Array3f&);
	~DirectionalLight();
	Eigen::Array3f phongShade(Shape&, const Eigen::Vector3f&, Eigen::Vector3f&);
	Ray createLightRay(const Eigen::Vector3f&);
};

