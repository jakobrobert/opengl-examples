#pragma once

#include "core/Renderer.hpp"
#include "core/gl/VertexArray.hpp"
#include "core/gl/VertexBuffer.hpp"

class TriangleRenderer : public Renderer
{
public:
    virtual bool onInit() override;
    virtual void onDestroy() override;
    virtual void onDraw() override;
private:
    VertexArray* m_vertexArray = nullptr;
    VertexBuffer* m_vertexBuffer = nullptr;
    unsigned int m_shader;
};
