#pragma once
#include "Includes.h"

class Ray {
	friend class RayTracer;
public:
	Ray(Eigen::Vector3f, Eigen::Vector3f, float, float);
	~Ray();

	bool withinBounds(float);
	Eigen::Vector3f rayAt(float);
	Eigen::Vector3f getDirection();
	Eigen::Vector3f getPosition();

protected:
	Eigen::Vector3f position;
	Eigen::Vector3f direction;

private:
	float _tMin;
	float _tMax;
};
