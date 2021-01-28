#include <core/OrthographicCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera()
:   m_viewMatrix(1.0f),
    m_projectionMatrix(1.0f)
{}

void OrthographicCamera::setPosition(const glm::vec2& position)
{
    m_position = position;
    updateViewMatrix();
}

void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
{
    m_projectionMatrix = glm::ortho(left, right, bottom, top);
}

void OrthographicCamera::updateViewMatrix()
{
    m_viewMatrix = glm::mat4(1.0f);

    // multiplication order is in reverse order in which the matrices are applied
    // first translation, then scale, then rotation
    // for view matrix, all transformations are inverted
    // -> move camera to the right = move world to the left etc.
    m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(-m_position, 0.0f));
}
