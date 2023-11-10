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
	std::vector<PointLight*> m_pointLights;
	std::vector<SpotLight*> m_spotLights;
	std::vector<Object*> m_objects;
	std::vector<unsigned int> m_textures;
	std::string m_path = "..\\Resources\\";
	bool useNM = false;

	void render();
	void UpdateUniforms();
	void UpdateSpotLight();
	void DrawObject(Object* m_object);
	glm::vec3 makeRandom(glm::vec3 lower, glm::vec3 upper);
};
