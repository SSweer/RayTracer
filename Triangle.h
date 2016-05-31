#pragma once
#include "Shape.h"
#include <vector>

class Triangle : public Shape {
public:
	Triangle();
	Triangle(Eigen::Vector3f, Eigen::Vector3f, Eigen::Vector3f);
	~Triangle();

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
	std::vector<Eigen::Vector3f> _vertices;
	Eigen::Vector3f _normal;
	Eigen::Vector3f _edge0;
	Eigen::Vector3f _edge1;
};

