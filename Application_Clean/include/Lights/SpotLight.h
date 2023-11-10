#pragma once

#include "PointLight.h"

class SpotLight : public PointLight {
public:
	SpotLight(glm::vec3 colour, glm::vec3 position, glm::vec3 dir, glm::vec2 radii, glm::vec3 constants = glm::vec3(1.0, 0.027, 0.0028));
	~SpotLight() { --sTotal_; }
	void setLightUniforms(Shader* shader) override;
	void setDirection(glm::vec3& dir) { m_direction = dir; }
	void setRadii(glm::vec2& r) { m_radii = r; }
	glm::vec3& getDirection() { return m_direction; }
	glm::vec2& getRadii() { return m_radii; }
protected:
	static int sTotal_;
	glm::vec3 m_direction;
	glm::vec2 m_radii;
};
