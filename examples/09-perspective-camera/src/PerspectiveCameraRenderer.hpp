#pragma once

#include <vector>

#include <core/Renderer.hpp>
#include <core/gl/ShaderProgram.hpp>
#include <core/gl/VertexArray.hpp>
#include <core/gl/VertexBuffer.hpp>
#include <core/gl/IndexBuffer.hpp>
#include <core/gl/Texture.hpp>
#include <core/Transform2D.hpp>
#include <core/PerspectiveCamera.hpp>

class PerspectiveCameraRenderer : public Renderer
{
public:
    virtual bool onInit() override;
    virtual void onDestroy() override;
    virtual void onResize(int width, int height) override;
    virtual void onUpdate(const class Window& window, float frameTime) override;
    virtual void onDraw() override;
private:
    void updateObjects();
    void updateCamera(const class Window& window, float frameTime);
    void updateCameraTranslation(const class Window& window, float frameTime);
    void updateCameraRotation(const class Window &window, float frameTime);
private:
    ShaderProgram* m_shader = nullptr;
    VertexArray* m_vertexArray = nullptr;
    VertexBuffer* m_vertexBuffer = nullptr;
    IndexBuffer* m_indexBuffer = nullptr;
    Texture* m_texture = nullptr;
    PerspectiveCamera m_camera;

    std::vector<Transform2D> m_objectTransforms;

    int m_mvpMatrixUniformLocation = -1;
    int m_textureUniformLocation = -1;

    float m_elapsedTime = 0.0f;

    // speed in units per second
    static constexpr float CAMERA_MOVE_SPEED = 4.0f;
    static constexpr float CAMERA_ROTATION_SPEED = (float)(M_PI); // 180° per second
};
