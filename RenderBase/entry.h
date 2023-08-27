#pragma once
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

enum ShaderMode {
	NOTINITIALIZED = 0,
	SOURCE,
	CLASS,
};

struct ViewPortRGBA {
	float r;
	float g;
	float b;
	float a;
};

class OpenGLRenderEntry {
public:
	~OpenGLRenderEntry();

	int Initialize(const int width, const int height);
	void StartRender();
	void Finalize();  // 만들어 놨는데 소멸자 구현 안됨.

	void SetViewPortClearColor(ViewPortRGBA newColor) { this->viewPortClearColor = newColor; }

	void SetVertexPath(const char* vertexPathStr) { this->vertexPath = vertexPathStr; }
	void SetFragmentPath(const char* fragmentPathStr) { this->fragmentPath = fragmentPathStr; }

protected:
	/* 내부 사용 변수들*/
	GLFWwindow* currentWindow; // 현재 열려 있는 창
	ViewPortRGBA viewPortClearColor = { 0.2f, 0.3f, 0.3f, 1.0f }; // Viewport의 기본 초기화 색상. 필요시 override 하세요.

	// Default Vertex Shader
	const char* defaultVertexPath = "../RenderBase/defaultVertexShader.vs";
	// Default Fragment Shader
	const char* defaultFragmentPath = "../RenderBase/defaultFragmentShader.fs";
	
	// User Defined Vertex Shader
	const char* vertexPath = nullptr;
	// User Defined Fragment Shader
	const char* fragmentPath = nullptr;

	Shader* shaderClass;
	ShaderMode shaderMode = ShaderMode::NOTINITIALIZED;

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	/* 유틸리티 함수 */
	void processInput(GLFWwindow* window);


	GLFWwindow* GLFWInitialize(const int width, const int height);

	int LoadShader();

	virtual void PreRenderFunc() = 0;
	virtual void PrepareObjectBuffer(float vertices[], unsigned int indices[], int verticesSize, int indicesSize);
	virtual void RenderLoopFunc() = 0;

	// DEPRECATED
	// TODO: 다 지워도 될 듯. -> 기본 ShaderClass의 기본 쉐이더로 돌리면 됨.
	//unsigned int vertexShader;
	//unsigned int fragmentShader;
	//unsigned int shaderProgram;
	unsigned int ShaderCompile(const char* shaderSource, const int shaderType);

};