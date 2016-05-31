#include "Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
}

void Camera::instantiate(Eigen::Vector3f lookFrom, Eigen::Vector3f lookAt, Eigen::Vector3f up, float fov) {
	_e = lookFrom;

	_w = (_e - lookAt).normalized();
	_u = up.cross(_w).normalized();
	_v = _w.cross(_u).normalized();

	_fov = fov;
	_d = abs(lookAt(2) - _e(2));
}

void Camera::setScreen(Screen& screen) {
	_screen = screen;
}

Ray Camera::generateRay(Sample& sample) {
	float angle = tan((_fov / 2) * PI / 180);

	float i = ((2 * (sample.x + 0.5) - _screen.getWidth()) / _screen.getWidth()) * angle;
	float j = ((2 * (sample.y + 0.5) - _screen.getHeight()) / _screen.getHeight()) * angle;

	Eigen::Vector3f direction = i*_u + -j*_v + -_d*_w;
	return Ray(_e, direction, -INFINITY, INFINITY);
}
