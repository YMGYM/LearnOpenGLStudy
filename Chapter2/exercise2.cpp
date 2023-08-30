#include "RenderBase/entry.h"

class Chapter2Exercise2Renderer : public OpenGLRenderEntry {
	float xOffsetCounter = -1.0f;

	void OpenGLRenderEntry::PreRenderFunc() {
		float vertices[] = {
			-1.0f, -1.0f, 0.0f,
			 0.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
		};

		PrepareObjectBuffer(vertices, nullptr, sizeof(vertices), 0);
		SetVertexPath("Exercise2VShader.vs");
		SetFragmentPath("Exercise2FShader.fs");
	}

	void  OpenGLRenderEntry::RenderLoopFunc() {
		if (xOffsetCounter > 2.0)
		{
			xOffsetCounter = -2.0f;
		}
		else
		{
			xOffsetCounter += 0.01f;
		}

		shaderClass->setFloat("xOffset", xOffsetCounter);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};