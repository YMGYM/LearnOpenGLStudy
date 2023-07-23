#include "RenderBase/entry.h"

/*
Learn OpenGL 책 예제를 실행하기 위한 기본 렌더 방식.
모든 예제를 실행하기 위해서는 아래 방식으로 코드를 작성합니다.


startRender() 를 호출하면 아래 로직이 작동합니다.
1. PreRenderFunc() 가 한번 호출됩니다.
2. RenderLoop()가 매 프레임마다 호출됩니다.
3. startRender() 내부에서 미리 설정된 루프 탈출 조건을 확인하여 함수를 종료합니다..
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

		PrepareObjectBuffer(vertices, indices, sizeof(vertices), sizeof(indices));  // 의무적으로 실행해야 하는 함수 TODO: VBO, EBO, VAO를 동적으로 생성해서 사용하는 경우가 생기는 것 대응
	}


	void OpenGLRenderEntry::RenderLoopFunc() {
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
};

int main() {
	OpenGLRenderEntry* entryPoint = new RenderPlaygroundTestRenderer();
	
	entryPoint->SetViewPortClearColor({ 1.0f, 1.0f, 1.0f, 1.0f }); // 필요시 적용

	if (entryPoint->Initialize(800, 600) < 0) {
		return -1;
	}

	entryPoint->StartRender();

	entryPoint->Finalize();

	return 0;
}