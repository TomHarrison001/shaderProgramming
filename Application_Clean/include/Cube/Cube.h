#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"

class Cube {
public:
	Cube(glm::vec3 col, float shine, float specStrength);
	~Cube() {}
	void setCubeMaterialValues(Shader* shader);
	void setTransform(Shader* shader) { shader->setMat4("Model", m_transform); }
	void resetTransform() { m_transform = glm::mat4(1.0); }
	
	unsigned int& getVAO() { return m_VAO; }
	glm::mat4& getModelMatrix() { return m_transform; }
	unsigned int getIndicesCount() { return cubeIndices.size(); }
	
	void translate(glm::vec3 translation) { m_transform = glm::translate(m_transform, translation); }
	void rotate(float angle, glm::vec3 axis) { m_transform = glm::rotate(m_transform, angle, axis); }
	void scale(float scaleFactor, glm::vec3 axis) { m_transform = glm::scale(m_transform, scaleFactor * axis); }
protected:
	void makeVAO();
	unsigned int m_VBO, m_VAO, m_EBO;
	glm::mat4 m_transform;
	float m_shine;
	float m_specularStrength;
	glm::vec3 m_colour;

	std::vector<float> vertexData = {
		// back
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		// front
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		// left
		-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
		// right
		0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		// bottom
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
		// top
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f };
	std::vector<unsigned int> cubeIndices = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20 };
};
