#pragma once

#include <string>

class Texture
{
public:
    Texture(const std::string& filename);
    ~Texture();

    void bind(unsigned int unit) const;
    void unbind() const;
private:
    unsigned int m_id;
};
