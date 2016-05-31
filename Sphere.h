#pragma once
#include "Shape.h"

class Sphere : public Shape {
public:
	Sphere();
	Sphere(Eigen::Vector3f, float);
	~Sphere();

	Eigen::Vector3f getNormal(const Eigen::Vector3f&);
	float intersect(Eigen::Vector3f&, Eigen::Vector3f&);
	void applyTransformation(Eigen::Matrix4f&);
	void applyRotation(Eigen::Matrix3f&);

	Material& getMaterial();
	void setMaterial(Material&);

	const Eigen::Array3f ka();
	const Eigen::Array3f kd();
	const Eigen::Array3f ks();
	const Eigen::Array3f kr();
	const float sp();

private:
	float _radiusSquared;
	Eigen::Vector3f _center;
};

