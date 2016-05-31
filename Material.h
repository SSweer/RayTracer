#pragma once
#include <Eigen\Core>
#include <Eigen\Geometry>

class Material {
public:
	Material();
	~Material();

	Eigen::Array3f ka;
	Eigen::Array3f kd;
	Eigen::Array3f ks;
	Eigen::Array3f kr;
	float sp;
};

