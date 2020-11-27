#pragma once

#include <string>

#include "core/gl/OpenGLObject.hpp"

class ShaderProgram : public OpenGLObject
{
public:
    ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    virtual ~ShaderProgram();

    virtual void bind() const override;
    virtual void unbind() const override;

    int getAttribLocation(const std::string& name) const;
private:
    unsigned int m_id;
};
