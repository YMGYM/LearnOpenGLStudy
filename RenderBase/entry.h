#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

struct ViewPortRGBA {
	float r;
	float g;
	float b;
	float a;
};

class OpenGLRenderEntry {
public:
	int Initialize(const int width, const int height);
	void StartRender();
	void Finalize();

	void SetViewPortClearColor(ViewPortRGBA newColor) { this->viewPortClearColor = newColor; }

protected:
	/* 내부 사용 변수들*/
	GLFWwindow* currentWindow; // 현재 열려 있는 창
	ViewPortRGBA viewPortClearColor = { 0.2f, 0.3f, 0.3f, 1.0f }; // Viewport의 기본 초기화 색상. 필요시 override 하세요.
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	/* 유틸리티 함수 */
	void processInput(GLFWwindow* window);


	GLFWwindow* GLFWInitialize(const int width, const int height);

	int LoadShader();
	unsigned int ShaderCompile(const char* shaderSource, const int shaderType);

	virtual void PreRenderFunc() = 0;
	virtual void PrepareObjectBuffer(float vertices[], unsigned int indices[], int verticesSize, int indicesSize);

	virtual void RenderLoopFunc() = 0;
};