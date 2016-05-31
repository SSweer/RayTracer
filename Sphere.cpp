#include "Sphere.h"

Sphere::Sphere() {
}

Sphere::Sphere(Eigen::Vector3f center, float radius) {
	_center = center;
	_radiusSquared = powf(radius, 2);
}

Sphere::~Sphere() {
}

Eigen::Vector3f Sphere::getNormal(const Eigen::Vector3f& view) {
	return (view - _center).normalized();
}

float Sphere::intersect(Eigen::Vector3f& direction, Eigen::Vector3f& position) {
	Eigen::Vector3f originMinusCenter = position - _center;

	float a = direction.dot(direction);
	float b = 2 * originMinusCenter.dot(direction);
	float c = originMinusCenter.dot(originMinusCenter) - _radiusSquared;
	float discriminant = powf(b, 2) - 4 * a * c;

	if (discriminant < 0) {
		return NaN;
	}

	float t0 = (-b - sqrt(discriminant)) / (2 * a);
	float t1 = (-b + sqrt(discriminant)) / (2 * a);

	if (discriminant == 0) {
		return t0;
	}

	if (t0 < 0 && t1 < 0) {
		return NaN;
	}

	if (fmin(t0, t1) < 0) {
		return fmax(t0, t1);
	}

	return fmin(t0, t1);
}

void Sphere::applyTransformation(Eigen::Matrix4f& matrix) {
	Eigen::Vector4f center4Vector;
	center4Vector << _center, 1;
	Eigen::Vector4f newCenter = matrix * center4Vector;

	_center << newCenter(0), newCenter(1), newCenter(2);
}

void Sphere::applyRotation(Eigen::Matrix3f& matrix) {
	_center = matrix * _center;
}

Material& Sphere::getMaterial() {
	return _material;
}

void Sphere::setMaterial(Material& material) {
	_material = material;
}

const Eigen::Array3f Sphere::ka() {
	return _material.ka;
}

const Eigen::Array3f Sphere::kd() {
	return _material.kd;
}

const Eigen::Array3f Sphere::ks() {
	return _material.ks;
}

const Eigen::Array3f Sphere::kr() {
	return _material.kr;
}

const float Sphere::sp() {
	return _material.sp;
}