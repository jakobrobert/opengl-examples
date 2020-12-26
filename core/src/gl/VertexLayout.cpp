#include <core/gl/VertexLayout.hpp>

#include <glad/glad.h>

void VertexLayout::addAttribute(unsigned int location, unsigned int componentCount)
{
    VertexLayout::Attribute attribute;
    attribute.location = location;
    attribute.componentCount = componentCount;
    attribute.offsetInBytes = m_vertexSizeInBytes;
    m_vertexSizeInBytes += componentCount * sizeof(float);

    m_attributes.push_back(attribute);
}

void VertexLayout::enableAttributes() const
{
    for (const auto& attribute : m_attributes) {
        glEnableVertexAttribArray(attribute.location);
        glVertexAttribPointer(
            attribute.location, attribute.componentCount, GL_FLOAT, false,
            m_vertexSizeInBytes, (void*)(attribute.offsetInBytes)
        );
    }
}
