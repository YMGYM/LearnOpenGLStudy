#include "RenderBase/entry.h"

/*
Learn OpenGL å ������ �����ϱ� ���� �⺻ ���� ���.
��� ������ �����ϱ� ���ؼ��� �Ʒ� ������� �ڵ带 �ۼ��մϴ�.
startRender() �� ȣ���ϸ� �ڵ����� RenderLoop()�� �� �����Ӹ��� ȣ��˴ϴ�.
startRender() ���ο��� �̸� ������ ���� Ż�� ������ Ȯ���Ͽ� finalize()�� �����մϴ�.
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