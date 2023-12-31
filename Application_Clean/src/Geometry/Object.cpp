#pragma once

#include "Geometry/Object.h"

// Constructor takes in textures (loaded in myScene.cpp) and shine (default to 0.9)
Object::Object(unsigned int diffTexture, unsigned int specTexture, unsigned int normTexture, float shine) : 
	m_diffTexture(diffTexture), m_specTexture(specTexture), m_normTexture(normTexture), m_shine(shine) {}
// sets uniforms in the fragment shader for object attributes
void Object::setMaterialValues(Shader* shader) {
	shader->use();
	shader->setFloat("shine", m_shine);
	shader->setInt("diffuseMap", 0);
	shader->setInt("specularMap", 1);
	shader->setInt("normalMap", 2);

	glBindTextureUnit(0, m_diffTexture);
	glBindTextureUnit(1, m_specTexture);
	glBindTextureUnit(2, m_normTexture);
}
void Object::makeVAO() {
	// Create VBO (Vertex Buffer Object - unsigned ints storing texture, mesh, shader)
	glCreateBuffers(1, &m_VBO);
	// Creates and initialises a buffer object's immutable data store
	glNamedBufferStorage(m_VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);

	// Create Element Buffer
	glCreateBuffers(1, &m_EBO);
	glNamedBufferStorage(m_EBO, sizeof(unsigned int) * indices.size(), indices.data(), GL_DYNAMIC_STORAGE_BIT);

	// Creates VAO (Vertex Array Object - stores VBOs)
	glCreateVertexArrays(1, &m_VAO);
	// Binds a buffer to a vertex buffer bind point
	glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, sizeof(float) * m_strides);
	glVertexArrayElementBuffer(m_VAO, m_EBO);
    
	for (int i = 0; i < 4; i++) {
		// Turns on the array in VAO at specified index
		glEnableVertexArrayAttrib(m_VAO, i);
		// Specify the organisation of vertex arrays
		glVertexArrayAttribFormat(m_VAO, i, 3, GL_FLOAT, GL_FALSE, (3 * i - i / 3) * sizeof(float));
		// assign a vertex attribute to a vertex buffer binding for a vertex array object
		glVertexArrayAttribBinding(m_VAO, i, 0);
	}
}
