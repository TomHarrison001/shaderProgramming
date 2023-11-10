#pragma once

#include <iostream>
#include <random>
#include "MyScene.h"

MyScene::MyScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\vertShader.glsl", "..\\Shaders\\fragShader.glsl");

	// create directional light and set uniforms (colour: white, position: directly above)
	m_directionalLight = new DirectionalLight(glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, -1.0, 0.0));
	m_directionalLight->setLightUniforms(m_myShader);

	// creates point lights and set uniforms (one at each wall and one in the center)
	m_pointLights.push_back(new PointLight(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 4.9)));
	m_pointLights.push_back(new PointLight(glm::vec3(0.0, 1.0, 0.0), glm::vec3(4.9, 1.0, 0.0)));
	m_pointLights.push_back(new PointLight(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 1.0, -4.9)));
	m_pointLights.push_back(new PointLight(glm::vec3(1.0, 1.0, 0.0), glm::vec3(-4.9, 1.0, 0.0)));
	m_pointLights.push_back(new PointLight(glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0)));
	// makeRandom function can be used to generate random positions and colours

	for (PointLight* m_pointLight : m_pointLights) {
		m_pointLight->setLightUniforms(m_myShader);
	}

	// creates spot light attached to the camera using cam position and direction
	m_spotLights.push_back(new SpotLight(glm::vec3(1.0, 1.0, 1.0), m_camera->getPosition(), m_camera->getFront(), glm::vec2(glm::cos(glm::radians(7.5f)), glm::cos(glm::radians(12.5f)))));

	for (SpotLight* m_spotLight : m_spotLights) {
		m_spotLight->setLightUniforms(m_myShader);
	}

	// loads all textures once and stores in m_textures
	for (char const* file : { "diffuseCube.jpg", "specularCube.jpg", "normalCube.jpg", "diffuseFloor.jpg", "specularFloor.jpg", "normalFloor.jpg" }) {
		m_textures.push_back(TextureManager::loadTexture((m_path + file).c_str()));
	}

	// creates 2 cubes
	for (int i = 0; i < 2; i++) {
		m_objects.push_back(new Cube(m_textures[0], m_textures[1], m_textures[2]));
		m_objects[i]->translate(glm::vec3(4.0 * i - 2.0, 1.0, 0.0));
	}

	// creates 5 planes for walls and floor
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
	// deletes all pointers to release memory
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
	UpdateUniforms();
	UpdateSpotLight();

	// rotate Second Cube
	m_objects[1]->rotate((float)(glfwGetTime() / 1000.0f), glm::vec3(0.0, 1.0, 0.0));
	
	// draw all objects
	for (Object* m_object : m_objects) {
		DrawObject(m_object);
	}

	// toggles for Directional(1), Point(2), Spot(3) Lights and Normal Mapping(4)
	useDir = !m_handler->isKeyPressed(GLFW_KEY_1);
	usePoint = !m_handler->isKeyPressed(GLFW_KEY_2);
	useSpot = !m_handler->isKeyPressed(GLFW_KEY_3);
	useNM = !m_handler->isKeyPressed(GLFW_KEY_4);
}

// updates uniforms that change per frame
void MyScene::UpdateUniforms() {
	m_myShader->setMat4("Projection", m_camera->getProjectionMatrix());
	m_myShader->setMat4("View", m_camera->getViewMatrix());
	m_myShader->setVec3("viewPos", m_camera->getPosition());
	m_myShader->setBool("useDir", useDir);
	m_myShader->setBool("usePoint", usePoint);
	m_myShader->setBool("useSpot", useSpot);
	m_myShader->setBool("useNM", useNM);
}

// updates spot light uniforms for position and direction
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
