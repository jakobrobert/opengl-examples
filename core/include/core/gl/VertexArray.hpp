#pragma once

#include "core/gl/OpenGLObject.hpp"

class VertexArray : public OpenGLObject
{
public:
    VertexArray();
    virtual ~VertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    void setVertexAttribute(int location, unsigned int attributeSize, unsigned int vertexSize, unsigned int offset) const;
private:
    unsigned int m_id;
};
