#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "include/glad/glad.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#define POV 90.0f
#define NEAR 0.1f
#define FAR 10.0f

struct GLFWwindow;

class GLGame
{
public:
	GLGame(GLFWwindow* window) : GLWindow(window), MainCamera() { };
	~GLGame();

	void ClearVertexData();
	void AddVertexData(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat tx, GLfloat ty);

	void GLDraw();
	inline void UpdateViewMatrix() 
	{
		glm::mat4 view = MainCamera.GetViewMatrix();

		/*std::cout << std::endl;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				std::cout << view[i][j] << " , ";
			std::cout << std::endl;
		}*/

		glUniformMatrix4fv(ViewMatrixId, 1, false, &view[0][0]);
	}
	
	
	inline void UpdateProjectionMatrix(float screenWidth, float screenHeight)
	{
		glm::mat4 projection = glm::perspective(glm::radians(POV), screenWidth / screenHeight, NEAR, FAR);
		glUniformMatrix4fv(ProjectionMatrixId, 1, false, &projection[0][0]);
	}
	

	enum class ShaderType
	{
		FragmentShader = GL_FRAGMENT_SHADER,
		VertexShader = GL_VERTEX_SHADER
	};

	Camera& GetCamera() { return MainCamera; };

protected:
	GLFWwindow* GLWindow;
	Camera MainCamera;

	GLuint TransformMatrixId = 0;
	GLuint ProjectionMatrixId = 0;
	GLuint ViewMatrixId = 0;

	void InitializeGL(float screenWidth, float screenHeight);

private:
	// GL systems IDs
	GLuint GLProgramId = 0;
	GLuint VertexShaderId = 0;
	GLuint FragmentShaderId = 0;

	GLuint VertexBufferObjectId = 0;
	GLuint VertexArrayObjectId = 0;
	GLuint IndexBufferOBjectId = 0;

	void InitializeGLLogging();
	void InitializeVBO();
	void InitializeVAO();
	void InitializeIBO();

	void InitializeMatrixUniforms();
	void InitializePipeline();
	GLuint InitializeShader(ShaderType type, std::string file);
};