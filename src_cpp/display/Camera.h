#ifndef DISPLAY_CAMERA_H
#define DISPLAY_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace playground
{

class Camera
{

public:
	Camera();
	Camera(const glm::vec3 &transform); // Vector constructor.
	Camera(const float &x, const float &y, const float &z); // Scalar constructor.

	// Euler angles.
	float zoom = 45.0f;
	float yaw = -90.0f;
	float pitch = 0.0f;

	// Camera vectors.
	glm::vec3 transform;
	glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 frontVector = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 rightVector;
	glm::vec3 worldUpVector;

	glm::mat4 getViewMatrix();
	void handleOffset(const float &xOffset = 0.0f, const float &yOffset = 0.0f);

private:
	void updateVectors();

};

} // namespace playground

#endif // DISPLAY_CAMERA_H