#pragma once

#include <vector>

#include <core/Renderer.hpp>
#include <core/gl/ShaderProgram.hpp>
#include <core/gl/VertexArray.hpp>
#include <core/gl/VertexBuffer.hpp>
#include <core/gl/IndexBuffer.hpp>
#include <core/gl/Texture.hpp>
#include <core/Transform2D.hpp>
#include <core/OrthographicCamera.hpp>

class MultipleObjectsRenderer : public Renderer
{
public:
    virtual bool onInit() override;
    virtual void onDestroy() override;
    virtual void onResize(int width, int height) override;
    virtual void onUpdate(const class Window &window, float time) override;
    virtual void onDraw() override;
private:
    void updateCamera(const class Window &window);
    void updateCameraTranslation(const class Window &window);
    void updateCameraRotation(const class Window &window);
    void updateCameraScale(const class Window &window);
private:
    ShaderProgram* m_shader = nullptr;
    VertexArray* m_vertexArray = nullptr;
    VertexBuffer* m_vertexBuffer = nullptr;
    IndexBuffer* m_indexBuffer = nullptr;
    Texture* m_texture = nullptr;
    OrthographicCamera m_camera;

    std::vector<Transform2D> m_transforms;

    int m_mvpMatrixUniformLocation = -1;
    int m_textureUniformLocation = -1;

    static constexpr float CAMERA_MOVE_SPEED = 0.1f;
    static constexpr float CAMERA_ROTATION_SPEED = 0.1f;
    static constexpr float CAMERA_SCALE_SPEED_FACTOR = 1.02f;
};
