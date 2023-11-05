#pragma once

#include "Geometry/Cube.h"

Cube::Cube(glm::vec3 colour, float shine, float specStrength) : Object(colour, shine, specStrength) {
	setVertexData(vertexData);
	setIndices(indices);
	makeVAO();
	resetTransform();
}
