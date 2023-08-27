//#include "shadersUniform.cpp"
#include "shadersInterpolation.cpp"
//#include "shadersInterpolationClass.cpp"

int main() {
	/*OpenGLRenderEntry* entryPoint = new UniformShaderRenderer();*/
	OpenGLRenderEntry* entryPoint = new ShadersInterpolationRenderer();
	//OpenGLRenderEntry* entryPoint = new ShadersInterpolationClassRenderer();

	entryPoint->SetViewPortClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	if (entryPoint->Initialize(800, 600) < 0) {
		return -1;
	}

	entryPoint->StartRender();

	entryPoint->Finalize();

	return 0;
}