#pragma once

#include <Eigen\Core>
#include <Eigen\Geometry>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <vector>
#include <memory>

#define NaN -9999999;
#define PI 3.14159265
#define BLACK Eigen::Array3f(0, 0, 0);
#define OFFSET 0.01f;

inline bool notNan(int n) { return n != NaN; }

inline bool isBlack(Eigen::Array3f a) { return a(0) <= 0 && a(1) <= 0 && a(2) <= 0; }

inline float square(const float& a) {
	return a * a;
}

inline float distance(Eigen::Vector3f a, Eigen::Vector3f b) {
	return sqrt(square(a(0) - b(0)) + square(a(1) - b(1)) + square(a(2) - b(2)));
}