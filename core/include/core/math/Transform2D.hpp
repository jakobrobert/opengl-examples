#pragma once

#include <glm/glm.hpp>

class Transform2D
{
public:
    Transform2D();

    const glm::vec2& getTranslation() const { return m_translation; }
    void setTranslation(const glm::vec2& translation) { m_translation = translation; }

    const glm::vec2& getScale() const { return m_scale; }
    void setScale(const glm::vec2& scale) { m_scale = scale; }

    float getRotation() const { return m_rotation; }
    void setRotation(float rotation) { m_rotation = rotation; }

    glm::mat4 getModelMatrix() const;
private:
    glm::vec2 m_translation;
    glm::vec2 m_scale;
    float m_rotation;
};
