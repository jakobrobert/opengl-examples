#pragma once

#include "core/Renderer.hpp"
#include "core/gl/VertexBuffer.hpp"

class TriangleRenderer : public Renderer
{
public:
    virtual bool onInit() override;
    virtual void onDestroy() override;
    virtual void onDraw() override;
private:
    unsigned int m_vertexArray;
    VertexBuffer* m_vertexBuffer = nullptr;
    unsigned int m_shader;
};
