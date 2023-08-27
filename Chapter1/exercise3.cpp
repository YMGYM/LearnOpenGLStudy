#include "RenderBase/entry.h"

class Exercise3Renderer : public OpenGLRenderEntry {
	unsigned int shaderProgram;
	unsigned int VBOs[2];
	unsigned int VAOs[2];

	void OpenGLRenderEntry::PreRenderFunc() {
		float vertices[] = {
			-1.0f, -1.0f, 0.0f,
			-0.5f,  0.0f, 0.0f,
			 0.0f, -1.0f, 0.0f,
			 0.5f,  0.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
		};

		PrepareObjectBuffer(vertices, nullptr, sizeof(vertices), 0);


		// prepare another shader
		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
			"}\0";

		shaderProgram = glCreateProgram();
		unsigned int vertexShader = ShaderCompile(vertexShaderSource, GL_VERTEX_SHADER);
		unsigned int fragmentShader = ShaderCompile(fragmentShaderSource, GL_FRAGMENT_SHADER);

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram); // 컴파일 성공여부 체크
	}

	void  OpenGLRenderEntry::RenderLoopFunc() {
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgram);  // shaderProgram1을 호출하는 코드는 이 함수 밖에 존재
		glDrawArrays(GL_TRIANGLES, 2, 3);
	}
};