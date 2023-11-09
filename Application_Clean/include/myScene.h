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
	DirectionalLight* m_directionalLight;
	PointLight* m_pointLight;
	std::vector<PointLight*> m_pointLights;
	SpotLight* m_spotLight;
	std::vector<SpotLight*> m_spotLights;
	Object* m_object;
	std::vector<Object*> m_objects;
	unsigned int m_cubeDiffTexture, m_cubeSpecTexture, m_cubeNormTexture;
	unsigned int m_planeDiffTexture, m_planeSpecTexture, m_planeNormTexture;
	bool useNM = false;

	void render();
	glm::vec3 makeRandom(glm::vec3 lower, glm::vec3 upper);
};
