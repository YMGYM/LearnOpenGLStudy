#include "RenderBase/entry.h"

class ShadersInterpolationRenderer : public OpenGLRenderEntry {
	unsigned int shaderProgram2;

	void PrepareObjectBuffer(float vertices[], unsigned int indices[], int verticesSize, int indicesSize) {  // override
		glGenBuffers(1, &this->VBO);

		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void OpenGLRenderEntry::PreRenderFunc() {
		float vertices[] = {
			 0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,
		};

		PrepareObjectBuffer(vertices, nullptr, sizeof(vertices), 0);


		// prepare another shader
		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec3 aColor;\n"
			"out vec3 ourColor;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos, 1.0);\n"
			"   ourColor = aColor;\n"
			"}\0";

		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec3 ourColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(ourColor, 1.0);\n"
			"}\0";

		shaderProgram2 = glCreateProgram();
		unsigned int vertexShader2 = ShaderCompile(vertexShaderSource, GL_VERTEX_SHADER);
		unsigned int fragmentShader2 = ShaderCompile(fragmentShaderSource, GL_FRAGMENT_SHADER);

		glAttachShader(shaderProgram2, vertexShader2);
		glAttachShader(shaderProgram2, fragmentShader2);
		glLinkProgram(shaderProgram2); // 컴파일 성공여부 체크
	}

	void  OpenGLRenderEntry::RenderLoopFunc() {
		glUseProgram(shaderProgram2);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};