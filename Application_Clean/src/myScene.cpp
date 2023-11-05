#pragma once
#include "MyScene.h"
#include <random>

MyScene::MyScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\vertShader.glsl", "..\\Shaders\\fragShader.glsl");

	m_directionalLight = new DirectionalLight(glm::vec3(1.0, 1.0, 1.0), glm::vec3(-1.0, -1.0, -1.0));
	m_directionalLight->setLightUniforms(m_myShader);

	m_pointLight = new PointLight(glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.22, 0.02), 0);
	m_pointLights.push_back(m_pointLight);

	for (PointLight* m_pointLight : m_pointLights) {
		m_pointLight->setLightUniforms(m_myShader);
	}

	m_cube = new Cube(glm::vec3(0.1, 0.2, 0.5), 16, 0.9);
	m_plane = new Plane(glm::vec3(1.0, 1.0, 1.0), 16, 0.9);
}
MyScene::~MyScene() {
	delete m_myShader;
	delete m_directionalLight;
	for (PointLight* m_pointLight : m_pointLights) {
		delete m_pointLight;
	}
	for (SpotLight* m_spotLight : m_spotLights) {
		delete m_spotLight;
	}
	delete m_cube;
	delete m_plane;
}
void MyScene::update(float dt) {
	m_camera->update(dt);
	render();
}
void MyScene::render() {
	m_myShader->use();
	m_myShader->setMat4("Projection", m_camera->getProjectionMatrix());
	m_myShader->setMat4("View", m_camera->getViewMatrix());
	m_myShader->setVec3("viewPos", m_camera->getPosition());

	m_spotLight = new SpotLight(glm::vec3(1.0, 1.0, 1.0), m_camera->getPosition(), glm::vec3(1.0, 0.027, 0.0028), 0, m_camera->getFront(), glm::vec2(glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))));
	m_spotLight->setLightUniforms(m_myShader);

	m_cube->setMaterialValues(m_myShader);
	glBindVertexArray(m_cube->getVAO());
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_plane->setMaterialValues(m_myShader);
	glBindVertexArray(m_plane->getVAO());
	m_plane->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_plane->getIndicesCount(), GL_UNSIGNED_INT, 0);
}
glm::vec3 MyScene::makeRandom(glm::vec3 lower, glm::vec3 upper) {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> distribX(lower.x, upper.x);
	std::uniform_real_distribution<float> distribY(lower.y, upper.y);
	std::uniform_real_distribution<float> distribZ(lower.z, upper.z);
	glm::vec3 randVec = glm::vec3(distribX(gen), distribY(gen), distribZ(gen));

	return randVec;
}
