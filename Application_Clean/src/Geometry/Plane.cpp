#pragma once

#include "Geometry/Plane.h"

Plane::Plane(glm::vec3 colour, float shine, float specStrength) : Cube(colour, shine, specStrength) {}
void Plane::setPlaneMaterialValues(Shader* shader) {
	shader->use();
	shader->setVec3("planeColour", m_colour);
	shader->setFloat("planeShine", m_shine);
	shader->setFloat("planeSpecStrength", m_specularStrength);
}
