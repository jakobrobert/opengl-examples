#pragma once

#include "core/Renderer.hpp"

class TriangleRenderer : public Renderer
{
public:
    virtual bool onInit() override;
    virtual void onDestroy() override;
    virtual void onDraw() override;
private:
    unsigned int m_vertexArray;
    unsigned int m_vertexBuffer;
    unsigned int m_shader;
};
