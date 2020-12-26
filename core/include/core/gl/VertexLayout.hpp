#pragma once

#include <vector>

class VertexLayout
{
public:
    struct Attribute
    {
        unsigned int location;
        unsigned int componentCount;
        size_t offsetInBytes;
    };
public:
    void addAttribute(unsigned int location, unsigned int componentCount);
    void enableAttributes() const;
private:
    std::vector<Attribute> m_attributes;
    unsigned int m_vertexSizeInBytes = 0;
};
