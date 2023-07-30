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
		glGenBuffers(2, VBOs);  // VBO�� ������ �����͸� �����ϰ� �ִ� ������ ��.
		glGenVertexArrays(2, VAOs); // VAO �� ���� VBO�� Attrib Pointer�� �о� �� ���¸� ������.

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
		glEnableVertexAttribArray(0); // ��� Vertex�� Shader location 0���� Binding��
	}

	void OpenGLRenderEntry::RenderLoopFunc() {
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};