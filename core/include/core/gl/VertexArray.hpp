#pragma once

#include <core/gl/VertexLayout.hpp>

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void setVertexLayout(const VertexLayout& layout) const;
private:
    unsigned int m_id;
};
