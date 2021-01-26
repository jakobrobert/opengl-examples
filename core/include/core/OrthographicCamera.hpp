#pragma once

#include <glm/glm.hpp>

class OrthographicCamera
{
public:
    void setProjection(float left, float right, float bottom, float top);

    const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
private:
    glm::mat4 m_projectionMatrix;
};
