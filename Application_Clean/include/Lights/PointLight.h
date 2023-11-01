#pragma once

#include "Light.h"

class PointLight : public Light {
public:
	PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants);
	~PointLight() {}
	void setLightUniforms(Shader* shader) override;
	void setPosition(glm::vec3& pos) { m_position = pos; }
	void setConstants(glm::vec3& constants) { m_constants = constants; }
	glm::vec3& setPosition() { return m_position; }
	glm::vec3& setConstants() { return m_constants; }
protected:
	glm::vec3 m_position;
	glm::vec3 m_constants;
};
