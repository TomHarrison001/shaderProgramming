#pragma once

#include "Scene.h"
#include "Shader.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include "Geometry/Cube.h"
#include "Geometry/Plane.h"
#include "Textures/TextureManager.h"

class MyScene : public Scene {
public:
	MyScene(GLFWwindow* window, InputHandler* H);
	~MyScene();
	void update(float dt) override;
private:
	Shader* m_myShader;
	// var for directional light
	DirectionalLight* m_directionalLight;
	// vectors for point and spot lights, objects and textures
	std::vector<PointLight*> m_pointLights;
	std::vector<SpotLight*> m_spotLights;
	std::vector<Object*> m_objects;
	std::vector<unsigned int> m_textures;
	// path of resource files (textures)
	std::string m_path = "..\\Resources\\";
	// toggles for directional, point and spot lights and normal mapping
	bool useDir, usePoint, useSpot, useNM;
	// cube movement
	glm::vec3 m_cubePos;

	void render();
	void UpdateUniforms();
	void UpdateSpotLight();
	void DrawObject(Object* m_object);
	glm::vec3 makeRandom(glm::vec3 lower, glm::vec3 upper);
};
