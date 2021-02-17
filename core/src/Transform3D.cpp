#include <core/Transform3D.hpp>

#include <glm/gtc/matrix_transform.hpp>

Transform3D::Transform3D()
:   m_translation(),
    m_scale(1.0f, 1.0f, 1.0f),
    m_rotation(0.0f, 0.0f, 0.0f)
{}

glm::mat4 Transform3D::getModelMatrix() const
{
    // multiplication order is in reverse order
    // first scale, then rotation, then translation
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(m_translation));
    // rotation is composed of three matrices. one for each axis. transformation order is x, y, z
    modelMatrix = glm::rotate(modelMatrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::rotate(modelMatrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(m_scale));

    return modelMatrix;
}
