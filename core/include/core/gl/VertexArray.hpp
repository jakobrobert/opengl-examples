#pragma once

#include "core/gl/OpenGLObject.hpp"

class VertexArray : public OpenGLObject
{
public:
    VertexArray();
    virtual ~VertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;
private:
    unsigned int m_id;
};
