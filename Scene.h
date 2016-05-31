#pragma once
#include "Includes.h"
#include "Sample.h"
#include "RayTracer.h"
#include "Screen.h"
#include "Camera.h"

class Scene {
public:
	Scene();
	~Scene();
	Scene(shared_ptr<Screen>, shared_ptr<Camera>, shared_ptr<RayTracer>);
	void setUp();
	Sample sampler();
	void render();
	Eigen::Vector3f getColor(int);

private:
	int _row;
	int _column;
	int _numPoints;
	int _k;

	Sample* _points;
	shared_ptr<Screen> _screen;
	shared_ptr<Camera> _camera;
	shared_ptr<RayTracer> _raytracer;
};

