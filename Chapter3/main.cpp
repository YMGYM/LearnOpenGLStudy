#define STB_IMAGE_IMPLEMENTATION
// �̻��ϰ� �̰� ���� �־�� ��ŷ�� ������. (��� �ʿ�)

//#include "BasicTecture.cpp"
#include "TextureUnits.cpp"


int main() {
	//OpenGLRenderEntry* entryPoint = new BasicTextureRenderer();
	OpenGLRenderEntry* entryPoint = new TextureUnitRenderer();

	entryPoint->SetViewPortClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	if (entryPoint->Initialize(800, 600) < 0) {
		return -1;
	}

	entryPoint->StartRender();

	delete entryPoint;

	return 0;
}