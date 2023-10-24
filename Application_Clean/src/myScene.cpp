#pragma once
#include "MyScene.h"

MyScene::MyScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\vertShader.glsl", "..\\Shaders\\fragShader.glsl");
	makeVAO();
}
void MyScene::makeVAO() {
	// Create VBO (Vertex Buffer Object - unsigned ints storing texture, mesh, shader)
	glCreateBuffers(1, &VBO);
	// Creates and initialises a buffer object's immutable data store
	glNamedBufferStorage(VBO, sizeof(float) * 36, vertexData, GL_DYNAMIC_STORAGE_BIT);
	// Creates VAO (Vertex Array Object - stores VBOs)
	glCreateVertexArrays(1, &VAO);
	// Binds a buffer to a vertex buffer bind point
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 6);  // Stride: 6
	// Turns on the array in VAO at specified index
	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);
	// Specify the organisation of vertex arrays
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);  // normalised: GL_FALSE
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	// assign a vertex attribute to a vertex buffer binding for a vertex array object
	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribBinding(VAO, 1, 0);
}
void MyScene::update(float dt) {
	m_camera->update(dt);
	render();
}
void MyScene::render() {
	m_myShader->use();
	m_myShader->setFloat("time", sin((float)glfwGetTime()));
	// Bind a vertex array object
	glBindVertexArray(VAO);
	// Render primitives from bound array data
	glDrawArrays(GL_TRIANGLES, 0, 6);  // GLenummode: GL_TRIANGLES
}
