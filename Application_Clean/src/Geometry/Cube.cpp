#pragma once

#include "Geometry/Cube.h"

Cube::Cube(unsigned int diffTexture, unsigned int specTexture, float shine) : Object(diffTexture, specTexture, shine) {
	setVertexData(vertexData);
	setIndices(indices);
	makeVAO();
	resetTransform();
}
