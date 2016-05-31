#pragma once
#include "Includes.h"
#include <string>
#include <vector>
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Material.h"
#include "Screen.h"
#include "Camera.h"
#include "Transformations.h"

using namespace std;

class Parser {
public:
	Parser();
	~Parser();
	void parse(int argc, char *argv[], shared_ptr<Camera>, shared_ptr<Screen>,
		vector<Light*>&, vector<Shape*>&);
	void finalizeData(vector<Light*>&, vector<Shape*>&);

	vector<Material> materialsForShapes;

	int depth = 5;
	string filename;

	Transformations transforms;
};

