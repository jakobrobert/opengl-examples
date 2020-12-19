#pragma once

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    unsigned int getCount() const { return m_count; }

    void bind() const;
    void unbind() const;
private:
    unsigned int m_id;
    unsigned int m_count;
};
