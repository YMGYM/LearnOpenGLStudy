#include "shadersUniform.cpp"
#include "shadersInterpolation.cpp"
#include "shadersInterpolationClass.cpp"
#include "shadersUniformClass.cpp"

int main() {
	//OpenGLRenderEntry* entryPoint = new UniformShaderRenderer();
	//OpenGLRenderEntry* entryPoint = new ShadersInterpolationRenderer();
	//OpenGLRenderEntry* entryPoint = new ShadersInterpolationClassRenderer();
	OpenGLRenderEntry* entryPoint = new UniformShaderClassRenderer();

	entryPoint->SetViewPortClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	if (entryPoint->Initialize(800, 600) < 0) {
		return -1;
	}

	entryPoint->StartRender();

	delete entryPoint;
	entryPoint = nullptr;

	return 0;
}