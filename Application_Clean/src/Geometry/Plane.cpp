#pragma once

#include "Geometry/Plane.h"

Plane::Plane(unsigned int diffTexture, unsigned int specTexture, unsigned int normTexture, float shine) : Object(diffTexture, specTexture, normTexture, shine) {
	setVertexData(vertexData);
	setIndices(indices);
	makeVAO();
	resetTransform();
}
