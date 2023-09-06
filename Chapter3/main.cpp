#define STB_IMAGE_IMPLEMENTATION
// 이상하게 이게 여기 있어야 링킹에 성공함. (고민 필요)

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