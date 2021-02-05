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
    /*// multiplication order is in reverse order in which the matrices are applied
    // first rotation, then translation, then scale
    // all transformations are inverted
    // -> move camera to the right = move world to the left etc.
    glm::mat4 viewMatrix(1.0f);
    viewMatrix = glm::scale(viewMatrix, glm::vec3(m_scale, m_scale, 1.0f));
    viewMatrix = glm::translate(viewMatrix, glm::vec3(-m_translation, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, -m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));*/

    // first, build model matrix for the camera
    // TODO refactor
    Transform2D transform;
    transform.setTranslation(m_translation);
    transform.setScale(glm::vec2(m_scale, m_scale));
    transform.setRotation(m_rotation);
    glm::mat4 cameraModelMatrix = transform.getModelMatrix();

    // then inverse this matrix to get the view matrix
    // all transformations are inverted: i.e. moving camera to the right results into moving all models to the left etc.
    glm::mat4 viewMatrix = glm::inverse(cameraModelMatrix);

    return viewMatrix;
}
