#include "RenderBase/stb_image.h"

#include "RenderBase/entry.h"


class Exercise1Renderer : public OpenGLRenderEntry {
	unsigned int texture0, texture1; // Texture ID
	void OpenGLRenderEntry::PreRenderFunc() {
		// Generate Texture
		glGenTextures(1, &texture0);

		// activate first texture
		glBindTexture(GL_TEXTURE_2D, texture0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// image up-down flip (Texture 좌표계의 y와 맞게 수정)
		stbi_set_flip_vertically_on_load(true);

		// Load Image
		int width, height, nrChannels;
		unsigned char* data = stbi_load("../Chapter3/container.jpg", &width, &height, &nrChannels, 3);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture in texture 0" << std::endl;
		}

		stbi_image_free(data);

		// activate second texture

		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);  // bind 했기 때문에 texture1 에 대한 설정으로 변경

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Load Image
		data = stbi_load("../Chapter3/awesomeface.png", &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture in texture1" << std::endl;
		}

		stbi_image_free(data);

		float vertices[] = {
			 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  // top right
			 0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,  // bottom right
			-0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  // boottom left
			-0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  // top left
		};

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		SetVertexPath("BasicTextureVShader.vert"); // 지난 예제와 같은 Shader를 사용해도 무방함.
		SetFragmentPath("Exercise1FShader.frag");

		this->LoadShader(); // ShaderProgram Instancing
		this->shaderClass->use();
		this->shaderClass->setInt("texture1", 0);
		this->shaderClass->setInt("texture2", 1);
	}


	void OpenGLRenderEntry::RenderLoopFunc() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	~Exercise1Renderer() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
};