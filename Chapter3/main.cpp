#define STB_IMAGE_IMPLEMENTATION
// �̻��ϰ� �̰� ���� �־�� ��ŷ�� ������. (��� �ʿ�)

//#include "BasicTecture.cpp"
//#include "TextureUnits.cpp"
//#include "exercise1.cpp"
//#include "exercise2.cpp"
//#include "exercise3.cpp"
#include "exercise4.cpp"



int main() {
	//OpenGLRenderEntry* entryPoint = new BasicTextureRenderer();
	//OpenGLRenderEntry* entryPoint = new TextureUnitRenderer();
	//OpenGLRenderEntry* entryPoint = new Exercise1Renderer();
	//OpenGLRenderEntry* entryPoint = new Exercise2Renderer();
	//OpenGLRenderEntry* entryPoint = new Exercise3Renderer();
	OpenGLRenderEntry* entryPoint = new Exercise4Renderer();

	entryPoint->SetViewPortClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	if (entryPoint->Initialize(800, 600) < 0) {
		return -1;
	}

	entryPoint->StartRender();

	delete entryPoint;

	return 0;
}