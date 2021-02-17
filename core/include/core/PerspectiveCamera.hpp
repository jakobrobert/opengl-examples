#pragma once

#include <glm/glm.hpp>

#include <core/Transform3D.hpp>

class PerspectiveCamera
{
public:
    float getFov() const { return m_fov; }
    void setFov(float fov) { m_fov = fov; }

    float getAspectRatio() const { return m_aspectRatio; }
    void setAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; }

    float getNearPlane() const { return m_nearPlane; }
    void setNearPlane(float nearPlane) { m_nearPlane = nearPlane; }

    float getFarPlane() const { return m_farPlane; }
    void setFarPlane(float farPlane) { m_farPlane = farPlane; }

    const glm::vec3& getTranslation() const { return m_transform.getTranslation(); }
    void setTranslation(const glm::vec3& translation) { m_transform.setTranslation(translation); }

    const glm::vec3& getRotation() const { return m_transform.getRotation(); }
    void setRotation(const glm::vec3& rotation) { m_transform.setRotation(rotation); } 

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getViewProjectionMatrix() const;
private:
    float m_fov;
    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;
    Transform3D m_transform;
};
