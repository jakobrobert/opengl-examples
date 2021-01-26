#pragma once

#include <core/Renderer.hpp>
#include <core/gl/ShaderProgram.hpp>
#include <core/gl/VertexArray.hpp>
#include <core/gl/VertexBuffer.hpp>

class TriangleRenderer : public Renderer
{
public:
    virtual bool onInit() override;
    virtual void onDestroy() override;
    virtual void onResize(int width, int height) override;
    virtual void onUpdate(float time) override {}
    virtual void onDraw() override;
private:
    ShaderProgram* m_shader = nullptr;
    VertexArray* m_vertexArray = nullptr;
    VertexBuffer* m_vertexBuffer = nullptr;
};
