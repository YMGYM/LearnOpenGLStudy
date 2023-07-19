#include "RenderBase/entry.h"

/*
Learn OpenGL 책 예제를 실행하기 위한 기본 렌더 방식.
모든 예제를 실행하기 위해서는 아래 방식으로 코드를 작성합니다.
startRender() 를 호출하면 자동으로 RenderLoop()가 매 프레임마다 호출됩니다.
startRender() 내부에서 미리 설정된 루프 탈출 조건을 확인하여 finalize()를 실행합니다.
*/

class PlaygroundRenderEntry : public OpenGLRenderEntry {
	void RenderLoop() {
		return;
	}
};

int main() {
	OpenGLRenderEntry* entryPoint = new PlaygroundRenderEntry();

	entryPoint->initialize();
	entryPoint->startRender();
	entryPoint->finalize();
	return 0;
}