#include <core/PerspectiveCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 PerspectiveCamera::getProjectionMatrix() const
{
    return glm::perspective(m_fov, m_aspectRatio, m_nearPlane, m_farPlane);
}

glm::mat4 PerspectiveCamera::getViewMatrix() const
{
    // view matrix is the inverse of the model matrix
    // all transformations are inverted: i.e. moving camera to the right results into moving all models to the left etc.
    glm::mat4 modelMatrix = m_transform.getModelMatrix();
    return glm::inverse(modelMatrix);
}

glm::mat4 PerspectiveCamera::getViewProjectionMatrix() const
{
    // multiplication in reverse order
    return getProjectionMatrix() * getViewMatrix();
}
