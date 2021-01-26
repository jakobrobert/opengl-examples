#include <core/OrthographicCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
{
    m_projectionMatrix = glm::ortho(left, right, bottom, top);
}
