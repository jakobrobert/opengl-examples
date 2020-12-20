#include <core/Transform2D.hpp>

#include <glm/gtc/matrix_transform.hpp>

Transform2D::Transform2D()
:   m_translation(),
    m_scale(1.0f, 1.0f),
    m_rotation(0.0f)
{} 

glm::mat4 Transform2D::getModelMatrix() const
{
    // multiplication order is in reverse order in which the matrices are applied
    // first scale, then rotation, then translation
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(m_translation, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(m_scale, 1.0f));

    return modelMatrix;
}
