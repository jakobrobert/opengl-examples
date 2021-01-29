#pragma once

#include <glm/glm.hpp>

class OrthographicCamera
{
public:
    void setProjection(float left, float right, float bottom, float top);

    const glm::vec2& getTranslation() const { return m_translation; }
    void setTranslation(const glm::vec2& translation) { m_translation = translation; }

    float getScale() const { return m_scale; }
    void setScale(float scale) { m_scale = scale; }

    float getRotation() const { return m_rotation; }
    void setRotation(float rotation) { m_rotation = rotation; } 

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
private:
    float m_left;
    float m_right;
    float m_bottom;
    float m_top;

    glm::vec2 m_translation;
    float m_scale;
    float m_rotation;
};
