#pragma once
#include "Scene.h"
#include "Shader.h"
/*
Child Class of Scene
*/

class MyScene : public Scene {
public:
	MyScene(GLFWwindow* window, InputHandler* H);
	~MyScene() {};
	void update(float dt) override;
private:
	Shader* m_myShader;
	unsigned int VBO, VAO;
	float vertexData[18] = { 0.5, 0.5, 0.0, 1.0, 0.0, 0.0,
							-0.5, 0.5, 0.0, 0.0, 1.0, 0.0,
							-0.5, -0.5, 0.0, 0.0, 0.0, 1.0 };
	void makeVAO();
	void render();
};
