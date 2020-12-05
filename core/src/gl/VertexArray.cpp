#include "core/gl/VertexArray.hpp"

#include <glad/glad.h>

#include <iostream>

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

void VertexArray::setVertexAttribute(unsigned int location, unsigned int attributeSize, unsigned int vertexSize, unsigned int offset) const
{
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, attributeSize, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void *)(offset * sizeof(float)));
}

void VertexArray::setVertexLayout(const VertexLayout& layout) const
{
    std::cout << "vertex size: " << layout.getVertexSize() << std::endl;
    for (const auto& attribute : layout.getAttributes()) {
        // TODO implement
        std::cout << "attribute: " << attribute.location << ", " << attribute.size << ", " << attribute.offset << std::endl;
    }
}
