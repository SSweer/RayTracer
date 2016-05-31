#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Eigen::Vector3f& position, Eigen::Array3f& color) {
	_position = position;
	_color = color;
}

DirectionalLight::DirectionalLight() {
}


DirectionalLight::~DirectionalLight() {
}

Eigen::Array3f DirectionalLight::phongShade(Shape& shape, const Eigen::Vector3f& point, Eigen::Vector3f& view) {
	Eigen::Vector3f normal = shape.getNormal(point);
	Eigen::Vector3f normView = -view.normalized();
	Eigen::Vector3f light = -_position.normalized();

	Eigen::Vector3f h = (normView + light).normalized();
	Eigen::Array3f diffuse = fmaxf(light.dot(normal), 0) * shape.kd() * _color;
	Eigen::Array3f specular = pow(fmaxf(h.dot(normal), 0), shape.sp()) * shape.ks() * _color;

	return diffuse + specular;
}

Ray DirectionalLight::createLightRay(const Eigen::Vector3f& point) {
	return Ray(point, -_position.normalized(), 0.01, INFINITY);
}