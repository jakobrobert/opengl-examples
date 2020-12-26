#pragma once

#include <core/gl/VertexLayout.hpp>

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;
private:
    unsigned int m_id;
};
