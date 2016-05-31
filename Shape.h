#pragma once

#include "Includes.h"
#include "Material.h"


class Shape {
	friend class Parser;
public:
	virtual Eigen::Vector3f getNormal(const Eigen::Vector3f&) = 0;
	virtual float intersect(Eigen::Vector3f&, Eigen::Vector3f&) = 0;
	virtual void applyTransformation(Eigen::Matrix4f&) = 0;
	virtual void applyRotation(Eigen::Matrix3f&) = 0;
	
	virtual Material& getMaterial() = 0;
	virtual void setMaterial(Material&) = 0;

	virtual const Eigen::Array3f ka() = 0;
	virtual const Eigen::Array3f kd() = 0;
	virtual const Eigen::Array3f ks() = 0;
	virtual const Eigen::Array3f kr() = 0;
	virtual const float sp() = 0;

protected:
	Material _material;
	Eigen::Vector3f _normal;
};

