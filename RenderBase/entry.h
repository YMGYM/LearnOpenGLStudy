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
	/* ���� ��� ������*/
	GLFWwindow* currentWindow; // ���� ���� �ִ� â
	ViewPortRGBA viewPortClearColor = { 0.2f, 0.3f, 0.3f, 1.0f }; // Viewport�� �⺻ �ʱ�ȭ ����. �ʿ�� override �ϼ���.
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	/* ��ƿ��Ƽ �Լ� */
	void processInput(GLFWwindow* window);


	GLFWwindow* GLFWInitialize(const int width, const int height);

	int LoadShader();
	unsigned int ShaderCompile(const char* shaderSource, const int shaderType);

	virtual void PreRenderFunc() = 0;
	virtual void PrepareObjectBuffer(float vertices[], unsigned int indices[], int verticesSize, int indicesSize);

	virtual void RenderLoopFunc() = 0;
};