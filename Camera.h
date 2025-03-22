#pragma once

#include <glm/glm.hpp>

class Camera	// Make sure to take time in account
{
public:
	Camera() : CameraLocation(0.0f, 0.0f, 0.0f), ForwardVector(0.0f, 0.0f, -1.0f), UpVector(0.0f, 1.0f, 0.0f) {};

	glm::mat4 GetViewMatrix() const;
	inline glm::vec3 GetRightVector() { return glm::normalize(glm::cross(ForwardVector, UpVector)); }

	void MoveForward(float distance);
	void MoveBackwards(float distance);
	void MoveLeft(float distance);
	void MoveRight(float distance);
	void MoveUp(float distance);
	void MoveDown(float distance);

	void RotateX(double delta);
	void RotateY(double delta);
	void RotateZ(double delta);

	bool cameraChanged = false;

private:
	glm::vec3 CameraLocation;
	glm::vec3 ForwardVector;
	glm::vec3 UpVector;

	glm::vec4 CameraMatrix;
};