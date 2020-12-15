#include "core/gl/Texture.hpp"

#include <glad/glad.h>
#include <stb_image/stb_image.h>

Texture::Texture(const std::string& filename)
{
    // create texture
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    // unbind to leave clean state
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::bindToSlot(unsigned int slot) const
{
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
