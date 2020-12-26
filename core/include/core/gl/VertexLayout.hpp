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
    void addAttribute(unsigned int location, unsigned int size);
    void enableAttributes() const;
private:
    std::vector<Attribute> m_attributes;
    unsigned int m_vertexSize = 0;
};
