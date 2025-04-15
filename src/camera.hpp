#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm.hpp"

struct Camera {
	glm::vec3 pos; // Position
	glm::vec3 ang; // Rotation (Euler angles)
                     // rot.x = pitch (Y axis rotation)
                     // rot.y = yaw   (Z axis rotation)
                     // rot.z = roll  (X axis rotation)
	float fov;    // Vectical FOV
	float aspect; // Viewport aspect ratio

	Camera(const glm::vec3& pos, const glm::vec3& ang, float fov, float aspect); // Constructor

	glm::vec3 getForward() const; // Gets forward direction (local X vector direction)
	glm::vec3 getLeft() const;    // Gets left direction    (local Y vector direction)
	glm::vec3 getUp() const;      // Gets up direction      (local Z vector direction)

	glm::mat4 getView() const;    // Gets view matrix
	glm::mat4 getProj() const;    // Gets projection matrix

	glm::quat getRot() const;     // Gets quaternion, representing camera rotation
};

#endif // CAMERA_HPP
