#include "RenderBase/entry.h"

class Chapter2Exercise3Renderer : public OpenGLRenderEntry {
	float xOffsetCounter = -1.0f;

	void OpenGLRenderEntry::PreRenderFunc() {
		float vertices[] = {
			-1.0f, -1.0f, 0.0f,
			 0.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
		};

		PrepareObjectBuffer(vertices, nullptr, sizeof(vertices), 0);
		SetVertexPath("Exercise3VShader.vs");
		SetFragmentPath("Exercise3FShader.fs");
	}

	void  OpenGLRenderEntry::RenderLoopFunc() {
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};