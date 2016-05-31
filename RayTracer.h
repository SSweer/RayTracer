#pragma once
#include "Includes.h"
#include "Light.h"
#include "Shape.h"
#include "Ray.h"
#include "Sample.h"

using namespace std;

class RayTracer {
public:
	RayTracer();
	~RayTracer();
	RayTracer(int, vector<Light*>&, vector<Shape*>&);

	float rayHit(Shape*, Ray&);
	bool didHitAny(Ray&);

	Ray newLightRay(Light*, Eigen::Vector3f&);
	Ray newReflectionRay(Eigen::Vector3f&, Eigen::Vector3f&, Eigen::Vector3f&);

	Eigen::Vector3f doColor(Ray&, Sample&, Shape*, float, int);
	void trace(Ray&, int, Sample&, Shape*, float);
	void traceFromCamera(Ray&, Sample&);

private:
	int _threshold; //max recursion depth

	vector<Light*>& _lights = vector<Light*>();
	vector<Shape*>& _shapes = vector<Shape*>();

	int _numLights;
	int _numShapes;
};
