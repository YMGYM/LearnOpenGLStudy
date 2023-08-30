#include "RenderBase/entry.h"

class Chapter2Exercise1Renderer : public OpenGLRenderEntry {
	void OpenGLRenderEntry::PreRenderFunc() {
		float vertices[] = {
			-1.0f, -1.0f, 0.0f,
			 0.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
		};

		PrepareObjectBuffer(vertices, nullptr, sizeof(vertices), 0);
		SetVertexPath("Exercise1VShader.vs");
		SetFragmentPath("Exercise1FShader.fs");
	}

	void  OpenGLRenderEntry::RenderLoopFunc() {
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};