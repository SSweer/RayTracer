#include "PointLight.h"

PointLight::PointLight(Eigen::Vector3f& position, Eigen::Array3f& color) {
	_position = position;
	_color = color;
}

PointLight::PointLight() {
}


PointLight::~PointLight() {
}

Eigen::Array3f PointLight::phongShade(Shape& shape, const Eigen::Vector3f& point, Eigen::Vector3f& view) {
	Eigen::Vector3f normal = shape.getNormal(view);
	view = -view.normalized();
	Eigen::Vector3f light = (_position - point).normalized();

	Eigen::Vector3f h = (view + light).normalized();
	Eigen::Array3f diffuse = fmaxf(light.dot(normal), 0) * shape.kd() * _color;
	Eigen::Array3f specular = pow(fmaxf(h.dot(normal), 0), shape.sp()) * shape.ks() * _color;

	return diffuse + specular;
}

Ray PointLight::createLightRay(const Eigen::Vector3f& point) {
	return Ray(point, (_position - point).normalized(), 0.01, distance(point, _position));
}