#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(CameraLocation, CameraLocation + ForwardVector, UpVector);
}

void Camera::MoveForward(float distance)
{
	CameraLocation += ForwardVector * distance;
	cameraChanged = true;
}

void Camera::MoveBackwards(float distance)
{
	CameraLocation -= ForwardVector * distance;
	cameraChanged = true;
}

void Camera::MoveRight(float distance)
{
	CameraLocation += GetRightVector() * distance;
	cameraChanged = true;
}

void Camera::MoveLeft(float distance)
{
	CameraLocation -= GetRightVector() * distance;
	cameraChanged = true;
}

void Camera::MoveUp(float distance)
{
	CameraLocation += UpVector * distance;
	cameraChanged = true;
}

void Camera::MoveDown(float distance)
{
	CameraLocation -= UpVector * distance;
	cameraChanged = true;
}

void Camera::RotateX(double delta)
{
	UpVector = glm::rotate(UpVector, static_cast<float>(-delta * 0.001f), GetRightVector());
	ForwardVector = glm::rotate(ForwardVector, static_cast<float>(-delta * 0.001f), GetRightVector());
	cameraChanged = true;
}

void Camera::RotateY(double delta)
{
	ForwardVector = glm::rotate(ForwardVector, static_cast<float>(-delta * 0.001f), UpVector);
	cameraChanged = true;
}

void Camera::RotateZ(double delta)
{
	UpVector = glm::rotate(UpVector, static_cast<float>(-delta * 0.1f), ForwardVector);
	ForwardVector = glm::rotate(ForwardVector, static_cast<float>(-delta * 0.1f), ForwardVector);
	cameraChanged = true;
}

