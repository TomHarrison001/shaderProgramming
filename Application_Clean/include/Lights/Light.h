#pragma once

#include <glm/glm.hpp>
#include "Shader.h"

class Light {
public:
	Light(glm::vec3 colour) : m_colour(colour) {}
	~Light() {}
	virtual void setLightUniforms(Shader* shader) {}
protected:
	glm::vec3& getColour() { return m_colour; }
	void setColour(glm::vec3 colour) { m_colour = colour; }

	glm::vec3 m_colour;
};
