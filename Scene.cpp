#include "Scene.h"

Scene::Scene() {
}

Scene::~Scene() {
	free(_points);
}

void Scene::setUp() {
	_points = (Sample *)malloc(_numPoints * sizeof(Sample));
}

Sample Scene::sampler() {
	Sample sample(_row, _column);
	if (_k % _screen->getWidth() == 0) {
		_row = 0;
		_column++;
	}

	_row++;
	_k++;

	return sample;
}

void Scene::render() {
	int i = 0;
	while (i < _numPoints) {
		Sample sample = sampler();
		Ray ray = _camera->generateRay(sample);
		_raytracer->traceFromCamera(ray, sample);

		_points[i] = sample;
		i++;
	}
}

Eigen::Vector3f Scene::getColor(int i) {
	return _points[i].color;
}

Scene::Scene(shared_ptr<Screen> screen, shared_ptr<Camera> camera, shared_ptr<RayTracer> raytracer) {
	_screen = screen;
	_camera = camera;
	_raytracer = raytracer;
	_row = 0;
	_column = 0;
	_k = 0;
	_numPoints = screen->getWidth() * screen->getHeight();
}