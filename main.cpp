#include <iostream>
#include <fstream>
#include <string>

#include "Parser.h"
#include "RayTracer.h"
#include "Scene.h"
#include "WriteImage.h"

using namespace std;

int main(int argc, char *argv[]) {
	unique_ptr<Parser> parser(new Parser());
	shared_ptr<Camera> camera(new Camera());
	shared_ptr<Screen> screen(new Screen());

	vector<Shape*> shapesInScene = vector<Shape*>();
	vector<Light*> lightsInScene = vector<Light*>();

	parser->parse(argc, argv, camera, screen, lightsInScene, shapesInScene);

	shared_ptr<RayTracer> raytracer(new RayTracer(parser->depth, lightsInScene, shapesInScene));
	unique_ptr<Scene> scene(new Scene(screen, camera, raytracer));

	string output = parser->filename;
	int width = screen->getWidth();
	int height = screen->getHeight();
	
	scene->setUp();
	scene->render();

	WriteImage writeImage(*scene);
	writeImage.write(output, width, height);

	for (int i = 0; i < shapesInScene.size(); i++) {
		delete(shapesInScene[i]);
	}

	for (int k = 0; k < lightsInScene.size(); k++) {
		delete(lightsInScene[k]);
	}

	return 0;
}