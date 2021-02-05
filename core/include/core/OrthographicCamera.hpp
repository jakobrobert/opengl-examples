#pragma once

#include <glm/glm.hpp>

#include <core/Transform2D.hpp>

class OrthographicCamera
{
public:
    // TODO simplify, only pass vec2 viewportSize
    void setProjection(float left, float right, float bottom, float top);

    const glm::vec2& getTranslation() const { return m_transform.getTranslation(); }
    void setTranslation(const glm::vec2& translation) { m_transform.setTranslation(translation); }

    const glm::vec2& getScale() const { return m_transform.getScale(); }
    void setScale(const glm::vec2& scale) { m_transform.setScale(scale); }

    float getRotation() const { return m_transform.getRotation(); }
    void setRotation(float rotation) { m_transform.setRotation(rotation); } 

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
private:
    float m_left;
    float m_right;
    float m_bottom;
    float m_top;

    Transform2D m_transform;
};
