#pragma once

#include "core/util/VertexLayout.hpp"

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
