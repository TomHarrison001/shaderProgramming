#pragma once

#include "Geometry/Object.h"

class Plane : public Object {
public:
	Plane(glm::vec3 colour, float shine, float specStrength);
	~Plane() {}

protected:
	const float planeLevel = -2.0f;
	const float planeSize = 7.0f;
	
	std::vector<float> vertexData = {
		-planeSize, planeLevel, -planeSize, 0.0f, 1.0f, 0.0f,
		planeSize, planeLevel, -planeSize, 0.0f, 1.0f, 0.0f,
		planeSize, planeLevel, planeSize, 0.0f, 1.0f, 0.0f,
		-planeSize, planeLevel, planeSize, 0.0f, 1.0f, 0.0f,
	};
	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};
};
