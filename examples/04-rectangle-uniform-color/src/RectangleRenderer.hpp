#pragma once

#include "core/Renderer.hpp"
#include "core/gl/ShaderProgram.hpp"
#include "core/gl/VertexArray.hpp"
#include "core/gl/VertexBuffer.hpp"
#include "core/gl/IndexBuffer.hpp"

class RectangleRenderer : public Renderer
{
public:
    virtual bool onInit() override;
    virtual void onDestroy() override;
    virtual void onDraw() override;
private:
    ShaderProgram* m_shader = nullptr;
    VertexArray* m_vertexArray = nullptr;
    VertexBuffer* m_vertexBuffer = nullptr;
    IndexBuffer* m_indexBuffer = nullptr;

    int m_colorUniformLocation = -1;
};
