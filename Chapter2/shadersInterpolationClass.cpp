#include "RenderBase/entry.h"

class ShadersInterpolationClassRenderer : public OpenGLRenderEntry {
	void PrepareObjectBuffer(float vertices[], unsigned int indices[], int verticesSize, int indicesSize) {  // override
		glGenBuffers(1, &this->VBO);

		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void OpenGLRenderEntry::PreRenderFunc() {
		float vertices[] = {
			 0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,
		};

		PrepareObjectBuffer(vertices, nullptr, sizeof(vertices), 0);
		SetVertexPath("InterpolationVShader.vs");
		SetFragmentPath("InterpolationFShader.fs");
	}

	void  OpenGLRenderEntry::RenderLoopFunc() {
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};