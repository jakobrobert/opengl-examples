#pragma once

#include <vector>

class VertexLayout
{
public:
    struct Attribute
    {
        unsigned int location;
        unsigned int size;
        unsigned int offset;
    };
public:
    const std::vector<Attribute>& getAttributes() const { return m_attributes; }

    void addAttribute(unsigned int location, unsigned int size);
private:
    std::vector<Attribute> m_attributes;
    unsigned int m_vertexSize;
};
