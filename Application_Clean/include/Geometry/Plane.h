#pragma once

#include "Geometry/Object.h"

class Plane : public Object {
public:
	Plane(unsigned int diffTexture, unsigned int specTexture, unsigned int normTexture);
	~Plane() {}

protected:
	const float planeLevel = 0.0f;
	const float planeSize = 5.0f;
	
	std::vector<float> vertexData = {
		-planeSize, planeLevel, -planeSize, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		planeSize, planeLevel, -planeSize, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		planeSize, planeLevel, planeSize, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-planeSize, planeLevel, planeSize, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f
	};
	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};
};
