#include "RenderBase/entry.h"

class UniformShaderRenderer : public OpenGLRenderEntry {
	unsigned int shaderProgram;
	void OpenGLRenderEntry::PreRenderFunc() {
		float vertices[] = {
			-1.0f, -1.0f, 0.0f,
			 0.0f,  1.0f, 0.0f,
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
			"uniform vec4 ourColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = ourColor;\n"
			"}\0";

		shaderProgram = glCreateProgram();
		unsigned int vertexShader = ShaderCompile(vertexShaderSource, GL_VERTEX_SHADER);
		unsigned int fragmentShader = ShaderCompile(fragmentShaderSource, GL_FRAGMENT_SHADER);

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram); // 컴파일 성공여부 체크
	}

	void  OpenGLRenderEntry::RenderLoopFunc() {
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};