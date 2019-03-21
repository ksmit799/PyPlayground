#include "core/_Wrapper.h"
#include "scene/CameraNode.h"

#include <pybind11/pybind11.h>

#include <glm/gtc/matrix_transform.hpp>

namespace playground
{

namespace py = pybind11;

CameraNode::CameraNode() : transform(glm::vec3(0.0f, 0.0f, 0.0f)), worldUpVector(upVector)
{}

CameraNode::CameraNode(const glm::vec3 &transform) : transform(transform), worldUpVector(upVector)
{}

CameraNode::CameraNode(const float &x, const float &y, const float &z)
	: transform(glm::vec3(x, y, z)), worldUpVector(upVector)
{}

glm::mat4 CameraNode::getViewMatrix()
{
	return glm::lookAt(this->transform, this->transform + this->frontVector, this->upVector);
}

void CameraNode::handleOffset(const float &xOffset, const float &yOffset)
{
	this->yaw += xOffset;
	this->pitch += yOffset;

	// Handle constrain.
	/*
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	*/

	// Update vectors using new euler angles.
	this->updateVectors();
}

void CameraNode::updateVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->frontVector = glm::normalize(front);

	// Also re-calculate the Right and Up vector
	this->rightVector = glm::normalize(glm::cross(this->frontVector, this->worldUpVector)); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->upVector = glm::normalize(glm::cross(this->rightVector, this->frontVector));
}

void wrap_scene_cameranode(py::module &m)
{}

} // namespace playground