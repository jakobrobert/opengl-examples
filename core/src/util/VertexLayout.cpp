#include "core/util/VertexLayout.hpp"

void VertexLayout::addAttribute(unsigned int location, unsigned int size)
{
    VertexLayout::Attribute attribute;
    attribute.location = location;
    attribute.size = size;
    attribute.offset = m_vertexSize;
    m_vertexSize += size;

    m_attributes.push_back(attribute);
}
