#pragma once

#include <string>

class ShaderProgram
{
public:
    ShaderProgram(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename);
    ~ShaderProgram();

    void use() const;
    void unuse() const;

    int getAttributeLocation(const std::string& name) const;
    int getUniformLocation(const std::string& name) const;
private:
    unsigned int m_id;
};
