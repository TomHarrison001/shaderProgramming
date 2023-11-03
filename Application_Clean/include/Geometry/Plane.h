#pragma once

#include "Cube.h"

class Plane : public Cube {
public:
	Plane(glm::vec3 colour, float shine, float specStrength);
	~Plane() {}
	void setPlaneMaterialValues(Shader* shader);
protected:
	const float planeLevel = -2.0f;
	const float planeSize = 7.0f;
	
	std::vector<float> vertexData = {
		-planeSize, planeLevel, -planeSize, 0.0, 1.0, 0.0,
		planeSize, planeLevel, -planeSize, 0.0, 1.0, 0.0,
		planeSize, planeLevel, planeSize, 0.0, 1.0, 0.0,
		-planeSize, planeLevel, planeSize, 0.0, 1.0, 0.0,
	};
	std::vector<unsigned int> cubeIndices = {
		3,2,1,
		3,1,0
	};
};
