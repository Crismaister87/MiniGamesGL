#include "GLGame.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include <GLFW\glfw3.h>

void GLGame::InitializeGL(float screenWidth, float screenHeight)
{
	//InitializeGLLogging();

	InitializeVBO();
	InitializeVAO();
	InitializeIBO();
	InitializePipeline();
	InitializeMatrixUniforms();

	UpdateProjectionMatrix(screenWidth, screenHeight);
	UpdateViewMatrix();

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

GLGame::~GLGame()
{
	if (VertexShaderId)
	{
		glDetachShader(GLProgramId, VertexShaderId);
		glDeleteShader(VertexShaderId);
	}
	
	if (VertexShaderId)
	{
		glDetachShader(GLProgramId, FragmentShaderId);
		glDeleteShader(FragmentShaderId);
	}
	
	glDeleteProgram(GLProgramId);

	glDeleteBuffers(1, &VertexBufferObjectId);
	glDeleteBuffers(1, &IndexBufferOBjectId);
	glDeleteVertexArrays(1, &VertexArrayObjectId);
}

void GLGame::GLDraw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	if (MainCamera.cameraChanged)
	{
		UpdateViewMatrix(); // only when camera is updated
		MainCamera.cameraChanged = false;
	}
}

/***** Initialization *****/

void GLGame::InitializeGLLogging()
{
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		std::string message_str(message, length);
		std::cout << message_str << '\n';
		}, NULL);

	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
}

void GLGame::InitializeVBO()
{
	glGenBuffers(1, &VertexBufferObjectId);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObjectId);
}

void GLGame::InitializeVAO()
{
	glGenVertexArrays(1, &VertexArrayObjectId);
	glBindVertexArray(VertexArrayObjectId);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(0));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
}

void GLGame::InitializeIBO()
{
	glGenBuffers(1, &IndexBufferOBjectId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferOBjectId);
}

void GLGame::InitializePipeline()
{
	GLProgramId = glCreateProgram();

	// Compile and attach Vertex Shader
	if (VertexShaderId = InitializeShader(ShaderType::VertexShader, "Shaders/BasicVertex.shader"))
		glAttachShader(GLProgramId, VertexShaderId);
	else
	{
		std::cerr << "Vertex Shader Compilation Failed!\n";
		glfwSetWindowShouldClose(GLWindow, GLFW_TRUE);
	}
	
	// Compile and attach Fragment Shader
	if (FragmentShaderId = InitializeShader(ShaderType::FragmentShader, "Shaders/BasicFragment.shader"))
		glAttachShader(GLProgramId, FragmentShaderId);
	else
	{
		std::cerr << "Fragment Shader Compilation Failed!\n";
		glfwSetWindowShouldClose(GLWindow, GLFW_TRUE);
	}

	glLinkProgram(GLProgramId);
	glUseProgram(GLProgramId);
}

GLuint GLGame::InitializeShader(ShaderType type, std::string file)
{
	std::ifstream shaderFileReader(file);
	if (shaderFileReader.is_open())
	{
		GLuint shaderIndex = glCreateShader(static_cast<GLuint>(type));

		std::string shaderCode((std::istreambuf_iterator<char>(shaderFileReader)),
			std::istreambuf_iterator<char>());
		shaderFileReader.close();

		const char* shaderSource = shaderCode.c_str();
		glShaderSource(shaderIndex, 1, &shaderSource, nullptr);
		glCompileShader(shaderIndex);

		// logging
		GLint compileStatus = 0;
		glGetShaderiv(shaderIndex, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE) {
			GLint logLength = 0;
			glGetShaderiv(shaderIndex, GL_INFO_LOG_LENGTH, &logLength);

			std::vector<GLchar> log(logLength);
			glGetShaderInfoLog(shaderIndex, logLength, &logLength, log.data());
			std::cerr << std::endl << "Shader compile error: " << log.data() << std::endl;
			
			return 0;
		}

		return shaderIndex;
	}
	return 0;
}

void GLGame::InitializeMatrixUniforms()
{
	TransformMatrixId = glGetUniformLocation(GLProgramId, "u_ModelMatrix");
	ProjectionMatrixId = glGetUniformLocation(GLProgramId, "u_ProjectionMatrix");
	ViewMatrixId = glGetUniformLocation(GLProgramId, "u_ViewMatrix");
}




