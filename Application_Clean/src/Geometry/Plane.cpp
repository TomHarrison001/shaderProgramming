#pragma once

#include "Geometry/Plane.h"

Plane::Plane(char const* diffusePath, char const* specPath, float shine) : Object(diffusePath, specPath, shine) {
	setVertexData(vertexData);
	setIndices(indices);
	makeVAO();
	resetTransform();
}
