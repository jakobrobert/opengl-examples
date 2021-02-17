#pragma once

#include <cmath>

#include <core/Renderer.hpp>
#include <core/gl/ShaderProgram.hpp>
#include <core/gl/VertexArray.hpp>
#include <core/gl/VertexBuffer.hpp>
#include <core/gl/IndexBuffer.hpp>
#include <core/gl/Texture.hpp>
#include <core/Transform2D.hpp>
#include <core/OrthographicCamera.hpp>

class OrthographicCameraRenderer : public Renderer
{
public:
    virtual bool onInit() override;
    virtual void onDestroy() override;
    virtual void onResize(int width, int height) override;
    virtual void onUpdate(const class Window& window, float frameTime) override;
    virtual void onDraw() override;
private:
    void updateObject(const class Window& window);
    void updateCamera(const class Window& window, float frameTime);
    void updateCameraTranslation(const class Window& window, float frameTime);
    void updateCameraRotation(const class Window& window, float frameTime);
    void updateCameraScale(const class Window& window, float frameTime);
private:
    ShaderProgram* m_shader = nullptr;
    VertexArray* m_vertexArray = nullptr;
    VertexBuffer* m_vertexBuffer = nullptr;
    IndexBuffer* m_indexBuffer = nullptr;
    Texture* m_texture = nullptr;
    Transform2D m_transform;
    OrthographicCamera m_camera;

    int m_mvpMatrixUniformLocation = -1;
    int m_textureUniformLocation = -1;

    float m_elapsedTime = 0.0f;

    // speed in units per second
    static constexpr float CAMERA_MOVE_SPEED = 4.0f;
    static constexpr float CAMERA_ROTATION_SPEED = (float)(0.5 * M_PI); // 90° per second
    static constexpr float CAMERA_SCALE_SPEED = 2.0f;
};
