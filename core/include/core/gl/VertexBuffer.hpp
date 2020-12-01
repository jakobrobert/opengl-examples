#pragma once

#include "core/gl/OpenGLObject.hpp"

class VertexBuffer : public OpenGLObject
{
public:
    VertexBuffer(const float* data, unsigned int size);
    virtual ~VertexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;
private:
    unsigned int m_id;
};
