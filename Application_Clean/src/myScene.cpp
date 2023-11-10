#pragma once

#include <iostream>
#include <random>
#include "MyScene.h"

MyScene::MyScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\vertShader.glsl", "..\\Shaders\\fragShader.glsl");

	m_directionalLight = new DirectionalLight(glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, -1.0, 0.0));
	m_directionalLight->setLightUniforms(m_myShader);
	
	/*for (int i = 0; i < 5; i++) {
		m_pointLights.push_back(new PointLight(makeRandom(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0)), makeRandom(glm::vec3(-4.9, 0.1, -4.9), glm::vec3(4.9, 9.9, 4.9))));
	}*/
	
	m_pointLights.push_back(new PointLight(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 4.9)));
	m_pointLights.push_back(new PointLight(glm::vec3(0.0, 1.0, 0.0), glm::vec3(4.9, 1.0, 0.0)));
	m_pointLights.push_back(new PointLight(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 1.0, -4.9)));
	m_pointLights.push_back(new PointLight(glm::vec3(1.0, 1.0, 0.0), glm::vec3(-4.9, 1.0, 0.0)));
	m_pointLights.push_back(new PointLight(glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0)));

	for (PointLight* m_pointLight : m_pointLights) {
		m_pointLight->setLightUniforms(m_myShader);
	}

	m_spotLights.push_back(new SpotLight(glm::vec3(1.0, 1.0, 1.0), m_camera->getPosition(), m_camera->getFront(), glm::vec2(glm::cos(glm::radians(7.5f)), glm::cos(glm::radians(12.5f)))));

	for (SpotLight* m_spotLight : m_spotLights) {
		m_spotLight->setLightUniforms(m_myShader);
	}

	// Load Textures Once
	for (char const* file : { "diffuseCube.jpg", "specularCube.jpg", "normalCube.jpg", "diffuseFloor.jpg", "specularFloor.jpg", "normalFloor.jpg" }) {
		m_textures.push_back(TextureManager::loadTexture((m_path + file).c_str()));
	}

	for (int i = 0; i < 2; i++) {
		m_objects.push_back(new Cube(m_textures[0], m_textures[1], m_textures[2]));
		m_objects[i]->translate(glm::vec3(4.0 * i - 2.0, 1.0, 0.0));
	}

	for (int i = 0; i < 5; i++) {
		m_objects.push_back(new Plane(m_textures[3], m_textures[4], m_textures[5]));
		if (i == 0) continue;
		std::vector<glm::vec3> r = { glm::vec3(1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, -1.0) };
		m_objects[i + 2]->rotate(glm::pi<float>() / 2, r[i - 1]);
		std::vector<glm::vec3> t = { glm::vec3(0.0, -5.0, -5.0), glm::vec3(0.0, -5.0, 5.0), glm::vec3(5.0, -5.0, 0.0), glm::vec3(-5.0, -5.0, 0.0) };
		m_objects[i + 2]->translate(t[i - 1]);
	}
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
	if (m_handler->isKeyPressed(GLFW_KEY_Q)) {
		useNM = !useNM;
	}
}
void MyScene::render() {
	m_myShader->use();
	UpdateUniforms();
	UpdateSpotLight();

	// Rotate Second Cube
	m_objects[1]->rotate((float)(glfwGetTime() / 1000.0f), glm::vec3(0.0, 1.0, 0.0));
	
	for (Object* m_object : m_objects) {
		DrawObject(m_object);
	}
}

void MyScene::UpdateUniforms() {
	m_myShader->setMat4("Projection", m_camera->getProjectionMatrix());
	m_myShader->setMat4("View", m_camera->getViewMatrix());
	m_myShader->setVec3("viewPos", m_camera->getPosition());
	m_myShader->setBool("useNM", useNM);
}

void MyScene::UpdateSpotLight() {
	SpotLight* m_spotLight = m_spotLights[0];
	m_spotLight->setPosition(m_camera->getPosition());
	m_spotLight->setDirection(m_camera->getFront());
	m_spotLight->setLightUniforms(m_myShader);
}

void MyScene::DrawObject(Object* m_object) {
	m_object->setMaterialValues(m_myShader);
	glBindVertexArray(m_object->getVAO());
	m_object->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_object->getIndicesCount(), GL_UNSIGNED_INT, 0);
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
