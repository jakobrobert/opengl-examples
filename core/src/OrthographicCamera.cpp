#include <core/OrthographicCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 OrthographicCamera::getProjectionMatrix() const
{
    float left = -0.5 * m_viewportSize.x;
    float right = 0.5 * m_viewportSize.x;
    float bottom = -0.5 * m_viewportSize.y;
    float top = 0.5 * m_viewportSize.y;
    return glm::ortho(left, right, bottom, top);
}

glm::mat4 OrthographicCamera::getViewMatrix() const
{
    // view matrix is the inverse of the model matrix
    // all transformations are inverted: i.e. moving camera to the right results into moving all models to the left etc.
    glm::mat4 modelMatrix = m_transform.getModelMatrix();
    return glm::inverse(modelMatrix);
}

glm::mat4 OrthographicCamera::getViewProjectionMatrix() const
{
    // multiplication in reverse order
    return getProjectionMatrix() * getViewMatrix();
}
