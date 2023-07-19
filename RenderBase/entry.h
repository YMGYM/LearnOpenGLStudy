#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class OpenGLRenderEntry {
public:
	void initialize();
	void startRender();
	void finalize();
	virtual void RenderLoop() = 0;
private:
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);
};