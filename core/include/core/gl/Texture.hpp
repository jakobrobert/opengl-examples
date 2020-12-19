#pragma once

#include <string>

class Texture
{
public:
    Texture(const std::string& filename);
    ~Texture();

    void bind() const;
    void unbind() const;

    // TODO: other bind is overkill, remove superclass? probably superclass is overkill 
    void bindToUnit(unsigned int unit) const;
private:
    unsigned int m_id;
};
