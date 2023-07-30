#include "RenderBase/entry.h"

class Exercise3Renderer : public OpenGLRenderEntry {
	unsigned int shaderProgram2;
	unsigned int fragmentShader2;
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
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
			"}\0";

		shaderProgram2 = glCreateProgram();
		unsigned int fragmentShader2 = ShaderCompile(fragmentShaderSource, GL_FRAGMENT_SHADER);

		glAttachShader(shaderProgram2, this->vertexShader);
		glAttachShader(shaderProgram2, fragmentShader2);
		glLinkProgram(shaderProgram2); // 컴파일 성공여부 체크
	}

	void  OpenGLRenderEntry::RenderLoopFunc() {
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgram2);  // shaderProgram1을 호출하는 코드는 이 함수 밖에 존재
		glDrawArrays(GL_TRIANGLES, 2, 3);
	}
};