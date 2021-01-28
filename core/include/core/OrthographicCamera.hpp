#pragma once

#include <glm/glm.hpp>

class OrthographicCamera
{
public:
    void setProjection(float left, float right, float bottom, float top);

    const glm::vec2& getPosition() const { return m_position; }
    void setPosition(const glm::vec2& position) { m_position = position; }

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
private:
    float m_left;
    float m_right;
    float m_bottom;
    float m_top;

    glm::vec2 m_position;
};
