#pragma once

#include <glm/glm.hpp>

class OrthographicCamera
{
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    glm::mat4 getProjectionMatrix() const;

private:
    glm::mat4 m_projectionMatrix;
};
