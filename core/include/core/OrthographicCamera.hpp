#pragma once

#include <glm/glm.hpp>

#include <core/Transform2D.hpp>

class OrthographicCamera
{
public:
    const glm::vec2& getViewportSize() const { return m_viewportSize; }
    void setViewportSize(const glm::vec2& viewportSize) { m_viewportSize = viewportSize; }

    const glm::vec2& getTranslation() const { return m_transform.getTranslation(); }
    void setTranslation(const glm::vec2& translation) { m_transform.setTranslation(translation); }

    const glm::vec2& getScale() const { return m_transform.getScale(); }
    void setScale(const glm::vec2& scale) { m_transform.setScale(scale); }

    float getRotation() const { return m_transform.getRotation(); }
    void setRotation(float rotation) { m_transform.setRotation(rotation); } 

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
private:
    glm::vec2 m_viewportSize;
    Transform2D m_transform;
};
