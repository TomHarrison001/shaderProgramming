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

	m_spotLight = new SpotLight(glm::vec3(1.0, 1.0, 1.0), m_camera->getPosition(), glm::vec3(1.0, 0.027, 0.0028), 0, m_camera->getFront(), glm::vec2(glm::cos(glm::radians(7.5f)), glm::cos(glm::radians(12.5f))));
	m_spotLights.push_back(m_spotLight);
	
	for (SpotLight* m_spotLight : m_spotLights) {
		m_spotLight->setLightUniforms(m_myShader);
	}

	m_object = new Cube("..\\Resources\\diffuseCube.jpg", "..\\Resources\\specularCube.jpg", 0.9);
	m_object->translate(glm::vec3(0.0, 1.0, 0.0));
	m_objects.push_back(m_object);
	m_object = new Plane("..\\Resources\\diffuseFloor.jpg", "..\\Resources\\specularFloor.jpg", 0.9);
	m_objects.push_back(m_object);
	m_object = new Plane("..\\Resources\\diffuseFloor.jpg", "..\\Resources\\specularFloor.jpg", 0.9);
	m_object->rotate(glm::pi<float>() / 2, glm::vec3(1.0, 0.0, 0.0));
	m_object->translate(glm::vec3(0.0, -7.5, -7.5));
	m_objects.push_back(m_object);
	m_object = new Plane("..\\Resources\\diffuseFloor.jpg", "..\\Resources\\specularFloor.jpg", 0.9);
	m_object->rotate(glm::pi<float>() / 2, glm::vec3(-1.0, 0.0, 0.0));
	m_object->translate(glm::vec3(0.0, -7.5, 7.5));
	m_objects.push_back(m_object);
	m_object = new Plane("..\\Resources\\diffuseFloor.jpg", "..\\Resources\\specularFloor.jpg", 0.9);
	m_object->rotate(glm::pi<float>() / 2, glm::vec3(0.0, 0.0, 1.0));
	m_object->translate(glm::vec3(7.5, -7.5, 0.0));
	m_objects.push_back(m_object);
	m_object = new Plane("..\\Resources\\diffuseFloor.jpg", "..\\Resources\\specularFloor.jpg", 0.9);
	m_object->rotate(glm::pi<float>() / 2, glm::vec3(0.0, 0.0, -1.0));
	m_object->translate(glm::vec3(-7.5, -7.5, 0.0));
	m_objects.push_back(m_object);
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
	for (Object* m_object : m_objects) {
		delete m_object;
	}
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

	m_spotLight = m_spotLights.front();
	m_spotLight->setPosition(m_camera->getPosition());
	m_spotLight->setDirection(m_camera->getFront());
	m_spotLight->setLightUniforms(m_myShader);

	for (Object* m_object : m_objects) {
		m_object->setMaterialValues(m_myShader);
		glBindVertexArray(m_object->getVAO());
		m_object->setTransform(m_myShader);
		glDrawElements(GL_TRIANGLES, m_object->getIndicesCount(), GL_UNSIGNED_INT, 0);
	}
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
