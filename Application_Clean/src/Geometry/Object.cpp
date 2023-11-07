#pragma once

#include "Geometry/Object.h"

Object::Object(glm::vec3 colour, float shine, float specStrength) : m_colour(colour), m_shine(shine), m_specStrength(specStrength) {}
void Object::setMaterialValues(Shader* shader) {
	shader->use();
	// shader->setVec3("objColour", m_colour);
	// shader->setFloat("objSpecStrength", m_specStrength);
	shader->setFloat("shine", m_shine);
	shader->setInt("diffuseMap", 0);
	shader->setInt("specularMap", 1);

	glBindTextureUnit(0, m_diffuseTexture);
	glBindTextureUnit(1, m_specularTexture);
}
void Object::makeVAO() {
	glCreateBuffers(1, &m_VBO);  // Create VBO (Vertex Buffer Object - unsigned ints storing texture, mesh, shader)
	glNamedBufferStorage(m_VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);  // Creates and initialises a buffer object's immutable data store

	glCreateBuffers(1, &m_EBO);  // Create Element Buffer
	glNamedBufferStorage(m_EBO, sizeof(unsigned int) * indices.size(), indices.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &m_VAO);  // Creates VAO (Vertex Array Object - stores VBOs)
	glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, sizeof(float) * m_strides);  // Binds a buffer to a vertex buffer bind point (stride: 6)
	glVertexArrayElementBuffer(m_VAO, m_EBO);
	glEnableVertexArrayAttrib(m_VAO, 0);  // Turns on the array in VAO at specified index
	glEnableVertexArrayAttrib(m_VAO, 1);
	glEnableVertexArrayAttrib(m_VAO, 2);
	glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);  // Specify the organisation of vertex arrays (normalised: GL_FALSE)
	glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribFormat(m_VAO, 2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float));
	glVertexArrayAttribBinding(m_VAO, 0, 0);  // assign a vertex attribute to a vertex buffer binding for a vertex array object
	glVertexArrayAttribBinding(m_VAO, 1, 0);
	glVertexArrayAttribBinding(m_VAO, 2, 0);
}
