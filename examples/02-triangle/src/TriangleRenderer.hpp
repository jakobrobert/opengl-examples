#pragma once

#include "core/Renderer.hpp"
#include "core/gl/VertexArray.hpp"
#include "core/gl/VertexBuffer.hpp"
#include "core/gl/ShaderProgram.hpp"

class TriangleRenderer : public Renderer
{
public:
    virtual bool onInit() override;
    virtual void onDestroy() override;
    virtual void onDraw() override;
private:
    VertexArray* m_vertexArray = nullptr;
    VertexBuffer* m_vertexBuffer = nullptr;
    ShaderProgram* m_shader = nullptr;
};
