#include "core/gl/VertexArray.hpp"

#include <glad/glad.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::setVertexAttrib(int location, unsigned int attribSize, unsigned int vertexSize, unsigned int offset) const
{
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, attribSize, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void *)(offset * sizeof(float)));
}
