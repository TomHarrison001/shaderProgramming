#pragma once

#include "Geometry/Plane.h"

Plane::Plane(unsigned int diffTexture, unsigned int specTexture, unsigned int normTexture) : Object(diffTexture, specTexture, normTexture) {
	setVertexData(vertexData);
	setIndices(indices);
	makeVAO();
	resetTransform();
}
