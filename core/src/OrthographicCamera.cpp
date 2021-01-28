#include <core/OrthographicCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera()
:   m_viewMatrix(1.0f),
    m_projectionMatrix(1.0f)
{}

void OrthographicCamera::setPosition(const glm::vec2& position)
{
    // TODO implement
}

void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
{
    m_projectionMatrix = glm::ortho(left, right, bottom, top);
}
