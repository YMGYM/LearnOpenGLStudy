#include "RenderBase/stb_image.h"

#include "RenderBase/entry.h"


class BasicTextureRenderer : public OpenGLRenderEntry {
	unsigned int texture;
	void OpenGLRenderEntry::PreRenderFunc() {
		// Generate Texture
		glGenTextures(1, &texture);

		// texture ������ Texture2D �� ���ε��մϴ�.
		glBindTexture(GL_TEXTURE_2D, texture);

		// texture ��Ÿ ������
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
			std::cout << "Failed to load texture" << std::endl;
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

		glGenBuffers(1, &this->VBO); // GPU�� buffer�� �����ϰ� ID ���� �޴´�
		glGenBuffers(1, &this->EBO);

		//OpenGL�� VAO �� ������ �׸��� ����. Buffer�� ���� ���ε� ������ ���� �ִ� ������Ʈ
		glGenVertexArrays(1, &this->VAO);

		// VAO�� VOB ���ε�
		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO); // ���� ������ Binding �Ѵ�. (GL_ARRAY_BUFFER �� ����� ������ VBO�� ����ϰڴ�)
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // �����͸� ī���ؼ� ���۷� �̵��մϴ�.
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		SetVertexPath("BasicTextureVShader.vert");
		SetFragmentPath("BasicTextureFShader.frag");
	}

	void OpenGLRenderEntry::RenderLoopFunc() {
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	~BasicTextureRenderer() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
};