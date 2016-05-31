#include "Ray.h"

Ray::Ray(Eigen::Vector3f position_, Eigen::Vector3f direction_, float tMin, float tMax) {
	position = position_;
	direction = direction_;
	_tMin = tMin;
	_tMax = tMax;
}

Ray::~Ray() {
}

Eigen::Vector3f Ray::getDirection() {
	return direction;
}

Eigen::Vector3f Ray::getPosition() {
	return position;
}



bool Ray::withinBounds(float t) {
	return (t >= _tMin && t < _tMax);
}

Eigen::Vector3f Ray::rayAt(float t) {
	return position + t * direction;
}