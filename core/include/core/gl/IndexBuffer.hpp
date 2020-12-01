#pragma once

#include "core/gl/OpenGLObject.hpp"

class IndexBuffer : public OpenGLObject
{
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    virtual ~IndexBuffer();

    unsigned int getCount() const { return m_count; }

    virtual void bind() const override;
    virtual void unbind() const override;
private:
    unsigned int m_id;
    unsigned int m_count;
};
