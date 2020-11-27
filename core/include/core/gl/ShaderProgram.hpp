#pragma once

#include <string>

#include "core/gl/OpenGLObject.hpp"

class ShaderProgram : public OpenGLObject
{
public:
    ShaderProgram(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename);
    virtual ~ShaderProgram();

    virtual void bind() const override;
    virtual void unbind() const override;

    int getAttributeLocation(const std::string& name) const;
private:
    unsigned int m_id;
};
