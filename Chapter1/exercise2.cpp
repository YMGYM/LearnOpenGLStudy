#include "RenderBase/entry.h"

class Exercise2Renderer : public OpenGLRenderEntry {
	unsigned int VBOs[2];
	unsigned int VAOs[2];


	void OpenGLRenderEntry::PreRenderFunc() {
		float vertices[2][9] = {
			{
				-1.0f, -1.0f, 0.0f,
				-0.5f,  0.0f, 0.0f,
				 0.0f, -1.0f, 0.0f,
			},
			{
				 0.0f, -1.0f, 0.0f,
				 0.5f,  0.0f, 0.0f,
				 1.0f, -1.0f, 0.0f,
			}
		};


		// this->Pre
		glGenBuffers(2, VBOs);  // VBO가 실제로 데이터를 저장하고 있는 역할을 함.
		glGenVertexArrays(2, VAOs); // VAO 는 현재 VBO와 Attrib Pointer를 읽어 온 상태를 저장함.

		glBindVertexArray(VAOs[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]), vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Second Triangle
		glBindVertexArray(VAOs[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[1]), vertices[1], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0); // 모든 Vertex를 Shader location 0번에 Binding함
	}

	void OpenGLRenderEntry::RenderLoopFunc() {
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};