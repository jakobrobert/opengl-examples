#include <core/OrthographicCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
{
    m_left = left;
    m_right = right;
    m_bottom = bottom;
    m_top = top;
}

glm::mat4 OrthographicCamera::getProjectionMatrix() const
{
    return glm::ortho(m_left, m_right, m_bottom, m_top);
}

glm::mat4 OrthographicCamera::getViewMatrix() const
{
    // multiplication order is in reverse order in which the matrices are applied
    // first translation, then scale, then rotation
    // all transformations are inverted
    // -> move camera to the right = move world to the left etc.
    glm::mat4 viewMatrix(1.0f);
    viewMatrix = glm::scale(viewMatrix, glm::vec3(m_scale, m_scale, 1.0f));
    viewMatrix = glm::translate(viewMatrix, glm::vec3(-m_translation, 0.0f));

    return viewMatrix;
}
