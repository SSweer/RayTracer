#include "Parser.h"

/* This class parses highly specialized command line input, a relic of this starting as a class assignent.
 * The general rule of thumb is that any object (ie. camera, triangle, pointlight) is then followed by any 
 * Position/color/transformation/etc. that shall be applied to it. */

Parser::Parser() {
	materialsForShapes = vector<Material>();
	Transformations transformations = Transformations();
}


Parser::~Parser() {
}

void Parser::parse(int argc, char *argv[], shared_ptr<Camera> camera, shared_ptr<Screen> screen,
	vector<Light*>& lightsInScene, vector<Shape*>& shapesInScene) {
	bool debug = true;
	char* current;

	int i = 1;
	while (i < argc) {
		current = argv[i];
		if (strcmp(current, "-size") == 0) {
			screen->instantiate(atoi(argv[i + 1]), atoi(argv[i + 2]));
			camera->setScreen(*screen);
			i += 3;
		} else if (strcmp(current, "-maxdepth") == 0) {
			depth = atoi(argv[i + 1]);
			i += 2;
		} else if (strcmp(current, "-out") == 0) {
			filename = string(argv[i + 1]);
			filename += ".ppm";
			i += 2;
		} else if (strcmp(current, "-camera") == 0) {
			Eigen::Vector3f lookFrom = Eigen::Vector3f(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
			Eigen::Vector3f lookAt = Eigen::Vector3f(atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
			Eigen::Vector3f up = Eigen::Vector3f(atof(argv[i + 7]), atof(argv[i + 8]), atof(argv[i + 9]));
			float fov = atof(argv[i + 10]);
			camera->instantiate(lookFrom, lookAt, up, fov);
			i += 11;
		} else if (strcmp(current, "-sphere") == 0) {
			Eigen::Vector3f center(Eigen::Vector3f(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3])));
			Sphere* sphere(new Sphere(center, atof(argv[i + 4])));
			shapesInScene.push_back(sphere);
			materialsForShapes.push_back(Material());
			i += 5;
		} else if (strcmp(current, "-triangle") == 0) {
			Eigen::Vector3f v1(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
			Eigen::Vector3f v2(atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
			Eigen::Vector3f v3(atof(argv[i + 7]), atof(argv[i + 8]), atof(argv[i + 9]));
			Triangle* triangle(new Triangle(v1, v2, v3));
			shapesInScene.push_back(triangle);
			materialsForShapes.push_back(Material());
			i += 10;
		} else if (strcmp(current, "-translate") == 0) {
			Matrix4f m = transforms.translationMatrix(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
			shapesInScene.back()->applyTransformation(m);
			i += 4;
		} else if (strcmp(current, "-scale") == 0) {
			Matrix4f m = transforms.scalarMatrix(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
			shapesInScene.back()->applyTransformation(m);
			i += 4;
		} else if (strcmp(current, "-shear") == 0) {
			Matrix4f m = transforms.shearMatrix(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]),
				atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
			shapesInScene.back()->applyTransformation(m);
			i += 7;
		} else if (strcmp(current, "-rotx") == 0) {
			Matrix3f m = transforms.rotateXMatrix(atof(argv[i + 1]));
			shapesInScene.back()->applyRotation(m);
			i += 2;
		} else if (strcmp(current, "-roty") == 0) {
			Matrix3f m = transforms.rotateYMatrix(atof(argv[i + 1]));
			shapesInScene.back()->applyRotation(m);
			i += 2;
		} else if (strcmp(current, "-rotz") == 0) {
			Matrix3f m = transforms.rotateZMatrix(atof(argv[i + 1]));
			shapesInScene.back()->applyRotation(m);
			i += 2;
		} else if (strcmp(current, "-dl") == 0) {
			Eigen::Vector3f pos(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
			Eigen::Array3f color(atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
			DirectionalLight* light(new DirectionalLight(pos, color));
			lightsInScene.push_back(light);
			i += 7;
		} else if (strcmp(current, "-pl") == 0) {
			Eigen::Vector3f pos(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
			Eigen::Array3f color(atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
			PointLight* light(new PointLight(pos, color));
			lightsInScene.push_back(light);
			i += 7;
		} else if (strcmp(current, "-ka") == 0) {
			materialsForShapes.back().ka =
				Eigen::Array3f(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
			i += 4;
		} else if (strcmp(current, "-kd") == 0) {
			materialsForShapes.back().kd =
				Eigen::Array3f(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
			i += 4;
		} else if (strcmp(current, "-ks") == 0) {
			materialsForShapes.back().ks =
				Eigen::Array3f(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
			i += 4;
		} else if (strcmp(current, "-sp") == 0) {
			materialsForShapes.back().sp = atof(argv[i + 1]);
			i += 2;
		} else if (strcmp(current, "-kr") == 0) {
			materialsForShapes.back().kr =
				Eigen::Array3f(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
			i += 4;
		} else {
			printf("invalid input: %s \n", current);
			break;
		}
	}

	finalizeData(lightsInScene, shapesInScene);
}

void Parser::finalizeData(vector<Light*>& lightsInScene, vector<Shape*>& shapesInScene) {
	if (shapesInScene.size() != materialsForShapes.size()) {
		return;
	}

	for (int i = 0; i < shapesInScene.size(); i++) {
		shapesInScene[i]->setMaterial(materialsForShapes[i]);
	}
}