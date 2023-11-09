#pragma once

#include "Geometry/Plane.h"

Plane::Plane(unsigned int diffTexture, unsigned int specTexture, float shine) : Object(diffTexture, specTexture, shine) {
	setVertexData(vertexData);
	setIndices(indices);
	makeVAO();
	resetTransform();
}
