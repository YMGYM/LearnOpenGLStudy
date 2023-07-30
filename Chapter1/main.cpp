#include "exercise1.cpp"
#include "exercise2.cpp"
#include "exercise3.cpp"


int main() {
	//OpenGLRenderEntry* entryPoint = new Exercise1Renderer();

	//OpenGLRenderEntry* entryPoint = new Exercise2Renderer();

	OpenGLRenderEntry* entryPoint = new Exercise3Renderer();

	entryPoint->SetViewPortClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	if (entryPoint->Initialize(800, 600) < 0) {
		return -1;
	}

	entryPoint->StartRender();

	entryPoint->Finalize();

	return 0;
}