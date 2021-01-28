#pragma once

#include <glm/glm.hpp>

class OrthographicCamera
{
public:
    OrthographicCamera();

    // TODO do not cache, create matrix in getter to be consistent with Transform2D
    const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
    const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }

    const glm::vec2& getPosition() const { return m_position; }
    void setPosition(const glm::vec2& position);

    void setProjection(float left, float right, float bottom, float top);
private:
    void updateViewMatrix();
private:
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;

    glm::vec2 m_position;
};
