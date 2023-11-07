#pragma once

#include "Geometry/Cube.h"

Cube::Cube(char const* diffusePath, char const* specPath, float shine) : Object(diffusePath, specPath, shine) {
	setVertexData(vertexData);
	setIndices(indices);
	makeVAO();
	resetTransform();
}
