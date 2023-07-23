#include "entry.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int OpenGLRenderEntry::Initialize(const int width, const int height) {
	this->currentWindow = GLFWInitialize(width, height);
	if (this->currentWindow == NULL) {
		return -1;
	}

	LoadShader();
	return 0;
}


void OpenGLRenderEntry::StartRender() {
	PreRenderFunc();

	while (!glfwWindowShouldClose(this->currentWindow)) {
		processInput(this->currentWindow);

		glClearColor(viewPortClearColor.r, viewPortClearColor.g, viewPortClearColor.b, viewPortClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(this->shaderProgram);

		this->RenderLoopFunc();

		glfwSwapBuffers(this->currentWindow);
		glfwPollEvents();
	}
}


void OpenGLRenderEntry::Finalize() {
	glfwTerminate();
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

/* PRIVATE FUNCTIONS */

void OpenGLRenderEntry::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
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
	// TODO: Shader Source �ϵ��ڵ��� �� �ٲٱ�
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

	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		return -1;
	}

	return 0;
}


unsigned int OpenGLRenderEntry::ShaderCompile(const char* shaderSource, const int shaderType) {
	int success;
	char infoLog[512];

	unsigned int targetShader;
	targetShader = glCreateShader(shaderType);

	glShaderSource(targetShader, 1, &shaderSource, NULL);
	glCompileShader(targetShader);

	glGetShaderiv(targetShader, GL_COMPILE_STATUS, &success); // shader ������ ���� ���� üũ

	if (!success) {
		glGetShaderInfoLog(targetShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		return -1;
	}

	glAttachShader(shaderProgram, targetShader);

	return targetShader;
}


void OpenGLRenderEntry::PrepareObjectBuffer(float vertices[], unsigned int indices[], int verticesSize, int indicesSize) {
	glGenBuffers(1, &this->VBO); // GPU�� buffer�� �����ϰ� ID ���� �޴´�

	//OpenGL�� VAO �� ������ �׸��� ����. Buffer�� ���� ���ε� ������ ���� �ִ� ������Ʈ

	glGenVertexArrays(1, &this->VAO);

	// VAO�� VOB ���ε�
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO); // ���� ������ Binding �Ѵ�. (GL_ARRAY_BUFFER �� ����� ������ VBO�� ����ϰڴ�)
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW); // �����͸� ī���ؼ� ���۷� �̵��մϴ�.

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Vertex �迭�� �д� ���� �����մϴ�.
	glEnableVertexAttribArray(0); // Vertex Attrib Pointer�� Enable�մϴ�.

	// EBO
	glGenBuffers(1, &this->EBO);

	// �� �������� GL_ARRAY_BUFFER�� GL_ELEMENT_ARRAY_BUFFER ���ε� ������ �����ϰ� �ִ�.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
}


/* PRIVATE FUNCTION END */

/* CALLBACK */
void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);  // TODO Ŭ���� ��� �Լ��� �ִ� �� ����� ����
}
