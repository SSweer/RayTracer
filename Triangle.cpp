#include "Triangle.h"

Triangle::Triangle() {
}

Triangle::Triangle(Eigen::Vector3f v0, Eigen::Vector3f v1, Eigen::Vector3f v2) {
	_vertices = { v0, v1, v2 };
	_edge0 = _vertices[1] - _vertices[0];
	_edge1 = _vertices[2] - _vertices[0];
	_normal = _edge0.cross(_edge1).normalized();
}

Triangle::~Triangle() {
}

Eigen::Vector3f Triangle::getNormal(const Eigen::Vector3f& view) {
	if (_normal.dot(-view) > 0) {
		return _normal;
	}

	return _edge1.cross(_edge0).normalized();
}

float Triangle::intersect(Eigen::Vector3f& direction, Eigen::Vector3f& position) {
	Eigen::Vector3f vertToPos = _vertices[0] - position;

	float a = -_edge0(0);
	float b = -_edge0(1);
	float c = -_edge0(2);

	float d = -_edge1(0);
	float e = -_edge1(1);
	float f = -_edge1(2);

	float g = direction(0);
	float h = direction(1);
	float i = direction(2);

	float j = vertToPos(0);
	float k = vertToPos(1);
	float l = vertToPos(2);

	float ei_minus_hf = e*i - h*f;
	float gf_minus_di = g*f - d*i;
	float dh_minus_eg = d*h - e*g;
	float ak_minus_jb = a*k - j*b;
	float jc_minus_al = j*c - a*l;
	float bl_minus_kc = b*l - k*c;

	float M = a*ei_minus_hf + b*gf_minus_di + c*dh_minus_eg;
	float t = -(f*ak_minus_jb + e*jc_minus_al + d*bl_minus_kc) / M;
	float gamma = (i*ak_minus_jb + h*jc_minus_al + g*bl_minus_kc) / M;

	if (gamma < 0 || gamma > 1) {
		return NaN;
	}

	float beta = (j*ei_minus_hf + k*gf_minus_di + l*dh_minus_eg) / M;
	if (beta < 0 || beta >(1 - gamma)) {
		return NaN;
	}

	return t;
}

void Triangle::applyTransformation(Eigen::Matrix4f& matrix) {
	for (int i = 0; i < _vertices.size(); i++) {
		Eigen::Vector4f vertexMatrix;
		vertexMatrix << _vertices[i], 1;
		vertexMatrix = matrix * vertexMatrix;
		_vertices[i] << vertexMatrix(0), vertexMatrix(1), vertexMatrix(2);
	}
}

void Triangle::applyRotation(Eigen::Matrix3f& matrix) {
	for (int i = 0; i < _vertices.size(); i++) {
		_vertices[i] = matrix * _vertices[i];
	}
}

Material& Triangle::getMaterial() {
	return _material;
}

void Triangle::setMaterial(Material& material) {
	_material = material;
}

const Eigen::Array3f Triangle::ka() {
	return _material.ka;
}

const Eigen::Array3f Triangle::kd() {
	return _material.kd;
}

const Eigen::Array3f Triangle::ks() {
	return _material.ks;
}

const Eigen::Array3f Triangle::kr() {
	return _material.kr;
}

const float Triangle::sp() {
	return _material.sp;
}