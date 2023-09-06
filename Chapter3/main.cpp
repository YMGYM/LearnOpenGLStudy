#define STB_IMAGE_IMPLEMENTATION
// �̻��ϰ� �̰� ���� �־�� ��ŷ�� ������. (��� �ʿ�)

#include "BasicTecture.cpp"


int main() {
	OpenGLRenderEntry* entryPoint = new BasicTextureRenderer();

	entryPoint->SetViewPortClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	if (entryPoint->Initialize(800, 600) < 0) {
		return -1;
	}

	entryPoint->StartRender();

	delete entryPoint;

	return 0;
}