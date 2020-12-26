#include <core/gl/VertexLayout.hpp>

#include <glad/glad.h>

void VertexLayout::addAttribute(unsigned int location, unsigned int size)
{
    VertexLayout::Attribute attribute;
    attribute.location = location;
    attribute.size = size;
    attribute.offset = m_vertexSize;
    m_vertexSize += size;

    m_attributes.push_back(attribute);
}

void VertexLayout::enableAttributes() const
{
    for (const auto& attribute : m_attributes) {
        glEnableVertexAttribArray(attribute.location);
        glVertexAttribPointer(
            attribute.location, attribute.size, GL_FLOAT, false,
            m_vertexSize * sizeof(float),
            (void*)(attribute.offset * sizeof(float))
        );
    }
}
