#pragma once

class VertexBuffer
{
public:
    VertexBuffer(const float* data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
private:
    unsigned int m_id;
};
