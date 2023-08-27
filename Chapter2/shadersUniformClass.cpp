#include "RenderBase/entry.h"

class UniformShaderClassRenderer : public OpenGLRenderEntry {
	void OpenGLRenderEntry::PreRenderFunc() {
		float vertices[] = {
			-1.0f, -1.0f, 0.0f,
			 0.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
		};

		PrepareObjectBuffer(vertices, nullptr, sizeof(vertices), 0);
		SetVertexPath("UniformVShader.vs");
		SetFragmentPath("UniformFShader.fs");
	}

	void  OpenGLRenderEntry::RenderLoopFunc() {
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderClass->ID, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};