#include <core/OrthographicCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
{
    m_projectionMatrix = glm::ortho(left, right, bottom, top);
}

glm::mat4 OrthographicCamera::getProjectionMatrix() const
{
    return m_projectionMatrix;
}
