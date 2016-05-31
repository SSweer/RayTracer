#include "WriteImage.h"


WriteImage::WriteImage(Scene& scene) {
	_scene = scene;
}


WriteImage::~WriteImage() {
}

void WriteImage::write(string filename, int height, int width) {
	ofstream imageFile;
	imageFile.open(filename.c_str());
	imageFile << "P3\n";
	imageFile << width << " " << height << "\n";

	int maxColorVal = 255;
	imageFile << maxColorVal;
	Eigen::Array3f color;

	int pixelCount = width*height;
	for (int i = 0; i < pixelCount; i++) {
		if ((i % width) == 0) {
			imageFile << "\n";
		}

		color = _scene.getColor(i);

		if (color(0) < 0.0001) color(0) = 0;
		if (color(1) < 0.0001) color(1) = 0;
		if (color(2) < 0.0001) color(2) = 0;

		int red = maxColorVal * color(0);
		int green = maxColorVal * color(1);
		int blue = maxColorVal * color(2);

		imageFile << red << " " << green << " " << blue << "    ";
	}

	imageFile.close();
}