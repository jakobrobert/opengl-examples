#include <core/OrthographicCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <core/Transform2D.hpp>

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
    // view matrix is the inverse of the model matrix
    // all transformations are inverted: i.e. moving camera to the right results into moving all models to the left etc.
    glm::mat4 modelMatrix = m_transform.getModelMatrix();
    return glm::inverse(modelMatrix);
}
