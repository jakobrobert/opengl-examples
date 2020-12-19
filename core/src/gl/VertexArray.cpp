#include <core/gl/VertexArray.hpp>

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

void VertexArray::setVertexLayout(const VertexLayout& layout) const
{
    for (const auto& attribute : layout.getAttributes()) {
        glEnableVertexAttribArray(attribute.location);
        glVertexAttribPointer(
            attribute.location, attribute.size,
            GL_FLOAT, GL_FALSE,
            layout.getVertexSize() * sizeof(float),
            (void*)(attribute.offset * sizeof(float))
        );
    }
}
