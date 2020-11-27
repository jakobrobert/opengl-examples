#pragma once

#include "core/gl/OpenGLObject.hpp"

class VertexArray : public OpenGLObject
{
public:
    VertexArray();
    virtual ~VertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    void setVertexAttrib(int location, unsigned int attribElementCount, unsigned int vertexElementCount, unsigned int offset) const;
private:
    unsigned int m_id;
};
