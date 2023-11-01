#pragma once
#include "Scene.h"
#include "Shader.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Cube/Cube.h"

class MyScene : public Scene {
public:
	MyScene(GLFWwindow* window, InputHandler* H);
	~MyScene();
	void update(float dt) override;
private:
	Shader* m_myShader;
	DirectionalLight* m_directionalLight;
	PointLight* m_pointLight;
	Cube* m_cube;

	void render();
};
