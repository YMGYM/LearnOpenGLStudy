#include "RenderBase/entry.h"

/*
Learn OpenGL å ������ �����ϱ� ���� �⺻ ���� ���.
��� ������ �����ϱ� ���ؼ��� �Ʒ� ������� �ڵ带 �ۼ��մϴ�.


startRender() �� ȣ���ϸ� �Ʒ� ������ �۵��մϴ�.
1. PreRenderFunc() �� �ѹ� ȣ��˴ϴ�.
2. RenderLoop()�� �� �����Ӹ��� ȣ��˴ϴ�.
3. startRender() ���ο��� �̸� ������ ���� Ż�� ������ Ȯ���Ͽ� �Լ��� �����մϴ�..
*/


class RenderPlaygroundTestRenderer : public OpenGLRenderEntry {
	void OpenGLRenderEntry::PreRenderFunc() {
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		PrepareObjectBuffer(vertices, indices, sizeof(vertices), sizeof(indices));  // �ǹ������� �����ؾ� �ϴ� �Լ� TODO: VBO, EBO, VAO�� �������� �����ؼ� ����ϴ� ��찡 ����� �� ����
	}


	void OpenGLRenderEntry::RenderLoopFunc() {
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
};

int main() {
	OpenGLRenderEntry* entryPoint = new RenderPlaygroundTestRenderer();
	
	entryPoint->SetViewPortClearColor({ 1.0f, 1.0f, 1.0f, 1.0f }); // �ʿ�� ����

	if (entryPoint->Initialize(800, 600) < 0) {
		return -1;
	}

	entryPoint->StartRender();

	entryPoint->Finalize();

	return 0;
}