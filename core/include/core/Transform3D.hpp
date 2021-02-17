#pragma once

#include <glm/glm.hpp>

class Transform3D
{
public:
    Transform3D();

    const glm::vec3& getTranslation() const { return m_translation; }
    void setTranslation(const glm::vec3& translation) { m_translation = translation; }

    const glm::vec3& getScale() const { return m_scale; }
    void setScale(const glm::vec3& scale) { m_scale = scale; }

    const glm::vec3& getRotation() const { return m_rotation; }
    void setRotation(const glm::vec3& rotation) { m_rotation = rotation; }

    glm::mat4 getModelMatrix() const;
private:
    glm::vec3 m_translation;
    glm::vec3 m_scale;
    glm::vec3 m_rotation;
};
