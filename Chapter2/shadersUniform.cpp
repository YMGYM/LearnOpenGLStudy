#include "RenderBase/entry.h"

class UniformShaderRenderer : public OpenGLRenderEntry {
	unsigned int shaderProgram2;
	void OpenGLRenderEntry::PreRenderFunc() {
		float vertices[] = {
			-1.0f, -1.0f, 0.0f,
			 0.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
		};

		PrepareObjectBuffer(vertices, nullptr, sizeof(vertices), 0);


		// prepare another shader
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"uniform vec4 ourColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = ourColor;\n"
			"}\0";

		shaderProgram2 = glCreateProgram();
		unsigned int fragmentShader2 = ShaderCompile(fragmentShaderSource, GL_FRAGMENT_SHADER);

		glAttachShader(shaderProgram2, this->vertexShader);
		glAttachShader(shaderProgram2, fragmentShader2);
		glLinkProgram(shaderProgram2); // 컴파일 성공여부 체크
	}

	void  OpenGLRenderEntry::RenderLoopFunc() {
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram2, "ourColor");
		glUseProgram(shaderProgram2);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};