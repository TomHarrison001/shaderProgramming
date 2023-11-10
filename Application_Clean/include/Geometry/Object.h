#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"

class Object {
public:
	Object(unsigned int diffTexture, unsigned int specTexture, unsigned int normTexture, float shine = 0.9);
	~Object() {}
	void setMaterialValues(Shader* shader);
	void setTransform(Shader* shader) { shader->setMat4("Model", m_transform); }
	void setVertexData(std::vector<float> data) { vertexData = data; }
	void setIndices(std::vector<unsigned int> i) { indices = i; }
	void resetTransform() { m_transform = glm::mat4(1.0); }

	unsigned int& getVAO() { return m_VAO; }
	glm::mat4& getModelMatrix() { return m_transform; }
	unsigned int getIndicesCount() { return indices.size(); }

	void translate(glm::vec3 translation) { m_transform = glm::translate(m_transform, translation); }
	void rotate(float angle, glm::vec3 axis) { m_transform = glm::rotate(m_transform, angle, axis); }
	void scale(float scaleFactor, glm::vec3 axis) { m_transform = glm::scale(m_transform, scaleFactor * axis); }
protected:
	void makeVAO();
	unsigned int m_VBO, m_VAO, m_EBO;
	unsigned int m_diffTexture, m_specTexture, m_normTexture;
	glm::mat4 m_transform;
	float m_shine;
	int m_strides = 11;

	std::vector<float> vertexData;
	std::vector<unsigned int> indices;
};
