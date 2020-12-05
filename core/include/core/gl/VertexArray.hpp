#pragma once

#include "core/gl/OpenGLObject.hpp"
#include "core/util/VertexLayout.hpp"

class VertexArray : public OpenGLObject
{
public:
    VertexArray();
    virtual ~VertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    void setVertexLayout(const VertexLayout& layout) const;
private:
    unsigned int m_id;
};
