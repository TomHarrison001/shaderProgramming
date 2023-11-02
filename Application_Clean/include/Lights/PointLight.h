#pragma once

#include "Light.h"

class PointLight : public Light {
public:
	PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants, int index);
	~PointLight() {}
	void setLightUniforms(Shader* shader) override;
	void setPosition(glm::vec3& pos) { m_position = pos; }
	void setConstants(glm::vec3& constants) { m_constants = constants; }
	glm::vec3& getPosition() { return m_position; }
	glm::vec3& getConstants() { return m_constants; }
	int& getIndex() { return m_index; }
protected:
	glm::vec3 m_position;
	glm::vec3 m_constants;
	int m_index;
};
