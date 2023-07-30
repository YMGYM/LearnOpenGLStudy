#include "RenderBase/entry.h"

class Exercise1Renderer : public OpenGLRenderEntry {

	void OpenGLRenderEntry::PreRenderFunc() {
		float vertices[] = {
			-1.0f, -1.0f, 0.0f,
			-0.5f,  0.0f, 0.0f,
			 0.0f, -1.0f, 0.0f,
			 0.5f,  0.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
		};

		PrepareObjectBuffer(vertices, nullptr, sizeof(vertices), 0);
	}

	void  OpenGLRenderEntry::RenderLoopFunc() {
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 2, 3);
	}
};