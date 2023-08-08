//#include "shadersUniform.cpp"
#include "shadersInterpolation.cpp"

int main() {
	/*OpenGLRenderEntry* entryPoint = new UniformShaderRenderer();*/
	OpenGLRenderEntry* entryPoint = new ShadersInterpolationRenderer();

	entryPoint->SetViewPortClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	if (entryPoint->Initialize(800, 600) < 0) {
		return -1;
	}

	entryPoint->StartRender();

	entryPoint->Finalize();

	return 0;
}