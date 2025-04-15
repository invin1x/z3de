#include "camera.hpp"

#include "gtc/quaternion.hpp"
#include "ext/quaternion_trigonometric.hpp"
#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

// Constructor
Camera::Camera
(
    const glm::vec3& pos,
    const glm::vec3& ang,
    float fov,
    float aspect
) : pos(pos),
    ang(ang),
    fov(fov),
    aspect(aspect) {}

// Gets forward direction (local X vector direction)
glm::vec3 Camera::getForward() const
{
    return glm::vec3(1, 0, 0) * getRot();
}

// Gets left direction (local Y vector direction)
glm::vec3 Camera::getLeft() const
{
    return glm::vec3(0, 1, 0) * getRot();
}

// Gets up direction (local Z vector direction)
glm::vec3 Camera::getUp() const
{
    return glm::vec3(0, 0, 1) * getRot();
}

// Gets view matrix
glm::mat4 Camera::getView() const
{
    return glm::lookAt(pos, pos + getForward(), getUp());
}

// Gets projection matrix
glm::mat4 Camera::getProj() const
{
    return glm::perspective(fov, aspect, 0.1f, 1e+6f);
}

// Gets quaternion, representing camera rotation
glm::quat Camera::getRot() const
{
    return glm::angleAxis(-ang.z, glm::vec3(1, 0, 0))
        * glm::angleAxis(-ang.x, glm::vec3(0, 1, 0))
        * glm::angleAxis(-ang.y, glm::vec3(0, 0, 1));
}
