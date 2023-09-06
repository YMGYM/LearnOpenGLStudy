#include "RenderBase/stb_image.h"

#include "RenderBase/entry.h"


class BasicTextureRenderer : public OpenGLRenderEntry {
	unsigned int texture;
	void OpenGLRenderEntry::PreRenderFunc() {
		// Generate Texture
		glGenTextures(1, &texture);

		// texture 변수는 Texture2D 에 바인드합니다.
		glBindTexture(GL_TEXTURE_2D, texture);

		// texture 기타 설정들
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

		glGenBuffers(1, &this->VBO); // GPU에 buffer를 생성하고 ID 값을 받는다
		glGenBuffers(1, &this->EBO);

		//OpenGL은 VAO 가 없으면 그리지 않음. Buffer에 대한 바인딩 정보를 갖고 있는 오브젝트
		glGenVertexArrays(1, &this->VAO);

		// VAO에 VOB 바인드
		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO); // 버퍼 유형을 Binding 한다. (GL_ARRAY_BUFFER 를 사용할 때마다 VBO를 사용하겠다)
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 데이터를 카피해서 버퍼로 이동합니다.
		
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