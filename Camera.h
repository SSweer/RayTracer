#pragma once
#include "Ray.h"
#include "Sample.h"
#include "Screen.h"

class Camera {
public:
	Camera();
	~Camera();
	void instantiate(Eigen::Vector3f, Eigen::Vector3f, Eigen::Vector3f, float);
	void setScreen(Screen&);
	Ray generateRay(Sample&);

private:
	Eigen::Vector3f _e, _w, _u, _v, _l, _r, _t, _b;
	float _d, _fov;
	Screen& _screen = Screen();
};

