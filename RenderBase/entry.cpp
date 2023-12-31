#include "entry.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);


OpenGLRenderEntry::~OpenGLRenderEntry()
{
	delete this->shaderClass;
	this->shaderClass = nullptr;
	Finalize();
}


int OpenGLRenderEntry::Initialize(const int width, const int height) {
	this->currentWindow = GLFWInitialize(width, height);
	if (this->currentWindow == NULL) {
		return -1;
	}
	return 0;
}


void OpenGLRenderEntry::StartRender() {
	PreRenderFunc();

	if (shaderMode == ShaderMode::NOTINITIALIZED)
	{
		LoadShader();
	}

	while (!glfwWindowShouldClose(this->currentWindow)) {
		processInput(this->currentWindow);

		glClearColor(viewPortClearColor.r, viewPortClearColor.g, viewPortClearColor.b, viewPortClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT);

		// Chapter2에서 변경함
 		if (shaderMode == ShaderMode::CLASS)
			this->shaderClass->use();
		//else
		//	glUseProgram(this->shaderProgram);

		this->RenderLoopFunc();

		glfwSwapBuffers(this->currentWindow);
		glfwPollEvents();
	}
}


void OpenGLRenderEntry::Finalize() {
	glfwTerminate();
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
}

/* PRIVATE FUNCTIONS */

void OpenGLRenderEntry::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		RenderKeyUpCallback();
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		RenderKeyDownCallback();
	}
}

GLFWwindow* OpenGLRenderEntry::GLFWInitialize(int width, int height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}


int OpenGLRenderEntry::LoadShader() {
	/* 이하 사용하지 않습니다. (Chaper 1 에서 사용했던 코드) */
	{
		/*if (!defaultVertexPath || !defaultFragmentPath) {
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
				"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
				"}\0";

			this->shaderProgram = glCreateProgram();
			this->vertexShader = ShaderCompile(vertexShaderSource, GL_VERTEX_SHADER);
			this->fragmentShader = ShaderCompile(fragmentShaderSource, GL_FRAGMENT_SHADER);

			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);
			glLinkProgram(shaderProgram);

			int success;
			char infoLog[512];
			glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);

			if (!success) {
				glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

				return -1;
			}
			this->shaderMode = ShaderMode::SOURCE;
		}
		else
		{
			// Vertex Shader나 Fragment Shader가 제공되지 않으면. 기본 코드를 실행
			this->shaderClass = new Shader(defaultVertexPath, defaultFragmentPath);
			this->shaderMode = ShaderMode::CLASS;
		}

		return 0;
		*/
	}

	// Vertex Shader나 Fragment Shader가 제공되지 않으면. 기본 코드를 실행
	// MEMO: 현재 Shader Class의 디자인 상 vs와 fs는 동시에 제공되어야 합니다.
	if (!vertexPath || !fragmentPath)
	{
		this->shaderClass = new Shader(defaultVertexPath, defaultFragmentPath);
	}
	else
	{
		this->shaderClass = new Shader(vertexPath, fragmentPath);

	}
	this->shaderMode = ShaderMode::CLASS;

	return 0;
}


unsigned int OpenGLRenderEntry::ShaderCompile(const char* shaderSource, const int shaderType) {
	/*
	* Chaper1, 2에서 Source를 통해 하드코딩 된 Shader를 넣을 때 사용합니다.
	* 이 함수를 직접적으로 재사용하는 부분이 있으므로 LoadShader가 주석처리 되어도 이 함수는 주석처리 하면 안 됩니다.
	*/
	int success;
	char infoLog[512];

	unsigned int targetShader;
	targetShader = glCreateShader(shaderType);

	glShaderSource(targetShader, 1, &shaderSource, NULL);
	glCompileShader(targetShader);

	glGetShaderiv(targetShader, GL_COMPILE_STATUS, &success); // shader 컴파일 성공 여부 체크

	if (!success) {
		glGetShaderInfoLog(targetShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		return -1;
	}

	return targetShader;
}


void OpenGLRenderEntry::PrepareObjectBuffer(float vertices[], unsigned int indices[], int verticesSize, int indicesSize) {
	glGenBuffers(1, &this->VBO); // GPU에 buffer를 생성하고 ID 값을 받는다

	//OpenGL은 VAO 가 없으면 그리지 않음. Buffer에 대한 바인딩 정보를 갖고 있는 오브젝트

	glGenVertexArrays(1, &this->VAO);

	// VAO에 VOB 바인드
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO); // 버퍼 유형을 Binding 한다. (GL_ARRAY_BUFFER 를 사용할 때마다 VBO를 사용하겠다)
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW); // 데이터를 카피해서 버퍼로 이동합니다.

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Vertex 배열을 읽는 법을 지정합니다.
	glEnableVertexAttribArray(0); // Vertex Attrib Pointer를 Enable합니다.

	if (indices != nullptr) {
		// EBO
		glGenBuffers(1, &this->EBO);

		// 이 시점에서 GL_ARRAY_BUFFER는 GL_ELEMENT_ARRAY_BUFFER 바인딩 정보를 저장하고 있다.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
	}
}


/* PRIVATE FUNCTION END */

/* CALLBACK */
void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);  // TODO 클래스 멤버 함수로 넣는 것 고민해 보기
}
