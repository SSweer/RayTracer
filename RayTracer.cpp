#include "RayTracer.h"

RayTracer::RayTracer() {
}

RayTracer::RayTracer(int depth, vector<Light*>& lights, vector<Shape*>& shapes) {
	_threshold = depth;
	_lights = lights;
	_shapes = shapes;

	_numLights = lights.size();
	_numShapes = shapes.size();
}

RayTracer::~RayTracer() {
}

float RayTracer::rayHit(Shape* shape, Ray& ray) {
	float t = shape->intersect(ray.getDirection(), ray.getPosition());
	if (!ray.withinBounds(t)) {
		return NaN;
	}

	return t;
}

bool RayTracer::didHitAny(Ray& ray) {
	for (int i = 0; i < _numShapes; i++) {
		float hit = rayHit(_shapes[i], ray);
		if (notNan(rayHit(_shapes[i], ray))) {
			return true;
		}
	}

	return false;
}

Ray RayTracer::newReflectionRay(Eigen::Vector3f& point, Eigen::Vector3f& normal, Eigen::Vector3f& direction) {
	Eigen::Vector3f dir = direction - 2 * direction.dot(normal) * normal;
	return Ray(point, dir, 0.01, INFINITY);
}

Ray RayTracer::newLightRay(Light* light, Eigen::Vector3f& point) {
	return light->createLightRay(point);
}
 
/* Traces ray from light to point on object to color. If it hits another object, colors
 * that point black, then moves on to the next light. */
Eigen::Vector3f RayTracer::doColor(Ray& ray, Sample& sample, Shape* shape, float t, int depth) {
	Eigen::Array3f color = BLACK;
	for (int i = 0; i < _numLights; i++) {
		Ray lightRay = newLightRay(_lights[i], ray.rayAt(t));
		bool hit = didHitAny(lightRay);

		if (!hit) {
			color = _lights[i]->phongShade(*shape, ray.rayAt(t), ray.direction);

			if (depth == 0) {
				sample.update(color);
			} else {
				sample.update(color * shape->kr());
			}
		}
	}

	return color;
}

/* Traces a ray from source, bouncing back to lights and other objects, if there is reflection.*/
void RayTracer::trace(Ray& ray, int depth, Sample& sample, Shape* shape, float t) {
	int hitObj = 0;
	bool hit = false;
	Eigen::Array3f color = BLACK;

	if (depth > _threshold) {
		return;
	}

	if (!notNan(t)) {
		return;
	}

	color = doColor(ray, sample, shape, t, depth);

	if (!isBlack(shape->kr()) && !isBlack(sample.color)) {
		Ray reflectionRay = newReflectionRay(ray.rayAt(t), shape->getNormal(ray.rayAt(t)), ray.direction);
		float d = INFINITY;
		for (int i = 0; i < _numShapes; i++) {
			float t = rayHit(_shapes[i], reflectionRay);
			if (notNan(t) && abs(t) < abs(d)) {
				d = t;
				hitObj = i;
				hit = true;
			}
		}

		if (hit) {
			trace(reflectionRay, depth++, sample, _shapes[hitObj], d);
		}
	}

	sample.update(shape->ka());
	sample.finalize();
}

void RayTracer::traceFromCamera(Ray& ray, Sample& sample) {
	int hitObj = 0;
	bool hit = false;
	float d = INFINITY;

	for (int i = 0; i < _numShapes; i++) {
		float t = rayHit(_shapes[i], ray);
		if (notNan(t) && abs(t) < abs(d)) {
			d = t;
			hitObj = i;
			hit = true;
		}
	}

	if (hit) {
		trace(ray, 0, sample, _shapes[hitObj], d);
	}
}