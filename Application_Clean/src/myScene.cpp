#pragma once
#include "MyScene.h"

MyScene::MyScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\vertShader.glsl", "..\\Shaders\\fragShader.glsl");
	makeVAO();
}
void MyScene::makeVAO() {
	glCreateBuffers(1, &VBO);  // Create VBO (Vertex Buffer Object - unsigned ints storing texture, mesh, shader)
	glNamedBufferStorage(VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);  // Creates and initialises a buffer object's immutable data store

	glCreateBuffers(1, &EBO);  // Create Element Buffer
	glNamedBufferStorage(EBO, sizeof(unsigned int) * indices.size(), indices.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &VAO);  // Creates VAO (Vertex Array Object - stores VBOs)
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 6);  // Binds a buffer to a vertex buffer bind point (stride: 6)
	glVertexArrayElementBuffer(VAO, EBO);
	glEnableVertexArrayAttrib(VAO, 0);  // Turns on the array in VAO at specified index
	glEnableVertexArrayAttrib(VAO, 1);
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);  // Specify the organisation of vertex arrays (normalised: GL_FALSE)
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribBinding(VAO, 0, 0);  // assign a vertex attribute to a vertex buffer binding for a vertex array object
	glVertexArrayAttribBinding(VAO, 1, 0);
}
void MyScene::update(float dt) {
	m_camera->update(dt);
	render();
}
void MyScene::render() {
	// get uniforms
	m_model = glm::mat4(1.0f);
	m_projection = m_camera->getProjectionMatrix();
	m_view = m_camera->getViewMatrix();
	// bind shader
	m_myShader->use();
	// set uniforms
	m_myShader->setMat4("Model", m_model);
	m_myShader->setMat4("Projection", m_projection);
	m_myShader->setMat4("View", m_view);

	m_myShader->setVec3("viewPos", m_camera->getPosition());
	m_myShader->setVec3("cubeColour", glm::vec3(0.5, 0.0, 0.0));
	m_myShader->setVec3("lightColour", glm::vec3(1.0, 1.0, 1.0));
	m_myShader->setVec3("lightDirection", glm::vec3(0.0, sin(glfwGetTime() * 5.0), cos(glfwGetTime() * 5.0)));

	m_myShader->setFloat("ambientFactor", 0.5);
	m_myShader->setFloat("shine", 64);
	m_myShader->setFloat("specStrength", 0.9);

	if (m_handler->keyHasBeenPressed()) {
		if (m_handler->isKeyPressed(GLFW_KEY_UP)) {
			// cubeJump();
			rot.y++;
		}
		if (m_handler->isKeyPressed(GLFW_KEY_RIGHT)) {
			// x_pos += 0.1f;
			rot.x++;
		}
		if (m_handler->isKeyPressed(GLFW_KEY_LEFT)) {
			// x_pos -= 0.1f;
			rot.z++;
		}
	}
	if (jumping) {
		pos += glm::vec3(0, (25 - jumpFrame) * 0.01f, 0);
		jumpFrame++;
		if (jumpFrame == 51)
			jumping = false;
	}
	m_model = glm::translate(m_model, pos);
	//m_model = glm::rotate(m_model, (float)(glfwGetTime() * 5.0), glm::vec3(0.0, 1.0, 0.0));
	//m_model = glm::rotate(m_model, 1000.f, rot);
	m_model = glm::scale(m_model, scale);

	m_myShader->setMat4("Model", m_model);
	// draw call
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, vertexData.size(), GL_UNSIGNED_INT, 0);
}
void MyScene::cubeJump() {
	if (jumping) return;
	jumping = true;
	jumpFrame = 0;
}
