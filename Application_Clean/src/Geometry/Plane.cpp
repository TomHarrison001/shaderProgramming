#pragma once

#include "Geometry/Plane.h"

Plane::Plane(glm::vec3 colour, float shine, float specStrength) : Object(colour , shine, specStrength) {
	setVertexData(vertexData);
	setIndices(indices);
	makeVAO();
	resetTransform();
}
