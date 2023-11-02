#pragma once
#include "MyScene.h"
#include <random>

MyScene::MyScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\vertShader.glsl", "..\\Shaders\\fragShader.glsl");

	m_directionalLight = new DirectionalLight(glm::vec3(1.0, 1.0, 1.0), glm::vec3(-1.0, -1.0, -1.0));
	m_directionalLight->setLightUniforms(m_myShader);

	/*m_pointLight = new PointLight(glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.22, 0.02), 0);
	m_pointLights.push_back(m_pointLight);
	m_pointLight = new PointLight(glm::vec3(0.0, 1.0, 0.0), glm::vec3(-1.0, 0.0, 0.0), glm::vec3(1.0, 0.22, 0.02), 1);
	m_pointLights.push_back(m_pointLight);*/

	for (int i = 0; i < 325; i++) {
		m_pointLight = new PointLight(makeRandom(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0)),
			makeRandom(glm::vec3(-10.0, -10.0, -10.0), glm::vec3(10.0, 10.0, 10.0)),
			glm::vec3(1.0, 0.22, 0.02),
				i);
		m_pointLights.push_back(m_pointLight);
	}

	for (PointLight* m_pointLight : m_pointLights) {
		m_pointLight->setLightUniforms(m_myShader);
	}

	m_cube = new Cube(glm::vec3(0.1, 0.2, 0.5), 16, 0.9);
	m_cube->setCubeMaterialValues(m_myShader);
}
MyScene::~MyScene() {
	delete m_myShader;
	delete m_directionalLight;

	for (PointLight* m_pointLight : m_pointLights) {
		delete m_pointLight;
	}

	delete m_cube;
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
	
	glBindVertexArray(m_cube->getVAO());
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);

	m_cube->translate(glm::vec3(5.0, 0.0, 0.0));
	m_cube->rotate((float)(glfwGetTime() * 0.5), glm::vec3(1.0, 0.0, 0.0));
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_cube->resetTransform();
}
glm::vec3 MyScene::makeRandom(glm::vec3 lower, glm::vec3 upper) {
	float range = 1.0f;
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> distribX(lower.x, upper.x);
	std::uniform_real_distribution<float> distribY(lower.y, upper.y);
	std::uniform_real_distribution<float> distribZ(lower.z, upper.z);
	glm::vec3 randVec = glm::vec3(distribX(gen), distribY(gen), distribZ(gen));

	return randVec;
}
