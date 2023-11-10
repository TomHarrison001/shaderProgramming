#pragma once

#include "Geometry/Cube.h"

Cube::Cube(unsigned int diffTexture, unsigned int specTexture, unsigned int normTexture) : Object(diffTexture, specTexture, normTexture) {
	setVertexData(vertexData);
	setIndices(indices);
	makeVAO();
	resetTransform();
}
