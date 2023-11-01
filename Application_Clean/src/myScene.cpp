#pragma once
#include "MyScene.h"

MyScene::MyScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\vertShader.glsl", "..\\Shaders\\fragShader.glsl");
	m_directionalLight = new DirectionalLight(glm::vec3(1.0, 1.0, 1.0), glm::vec3(-1.0, -1.0, -1.0));
	m_directionalLight->setLightUniforms(m_myShader);
	m_pointLight = new PointLight(glm::vec3(1.0, 0.0, 0.0), glm::vec3(-2.0, 0.0, 0.0), glm::vec3(1.0, 0.22, 0.02));
	m_pointLight->setLightUniforms(m_myShader);

	m_cube = new Cube(glm::vec3(0.1, 0.2, 0.5), 64, 16);
	m_cube->setCubeMaterialValues(m_myShader);
}
MyScene::~MyScene() {
	delete m_myShader;
	delete m_cube;
	delete m_directionalLight;
}
void MyScene::update(float dt) {
	m_camera->update(dt);
	render();
}
void MyScene::render() {
	// bind shader
	m_myShader->use();
	// set uniforms
	m_myShader->setMat4("Projection", m_camera->getProjectionMatrix());
	m_myShader->setMat4("View", m_camera->getViewMatrix());
	m_myShader->setVec3("viewPos", m_camera->getPosition());

	m_myShader->setVec3("plightPosition", glm::vec3(-2.0, 0.0, 0.0));
	m_myShader->setVec3("plightColour", glm::vec3(0.0, 1.0, 0.0));
	m_myShader->setVec3("pAttenuation", glm::vec3(1.0, 0.22, 0.02));
	
	glBindVertexArray(m_cube->getVAO());
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);

	m_cube->translate(glm::vec3(5.0, 0.0, 0.0));
	m_cube->rotate((float)(glfwGetTime() * 0.5), glm::vec3(1.0, 0.0, 0.0));
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_cube->resetTransform();
}
