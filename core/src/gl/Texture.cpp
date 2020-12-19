#include <core/gl/Texture.hpp>

#include <glad/glad.h>
#include <stb_image/stb_image.h>

#include <stdexcept>

Texture::Texture(const std::string& filename)
{
    // load image
    stbi_set_flip_vertically_on_load(true); // flip to fit opengl coord system
    int width, height, channels;
    int desiredChannels = 4; // convert to 4 channels (rgba) if it is not already
    stbi_uc* data = stbi_load(filename.c_str(), &width, &height, &channels, desiredChannels);
    if (!data) {
        throw std::runtime_error("Failed to load image from file '" + filename + "'!");
    }

    // create texture
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // upload image data to texture
    // first format: internal, how opengl stores it
    // second format: the provided format of the image data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // image data not required anymore because uploaded to texture
    stbi_image_free(data);

    // unbind to leave clean state
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

void Texture::bind(unsigned int unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
