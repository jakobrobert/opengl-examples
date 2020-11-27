#pragma once

class OpenGLObject
{
public:
    virtual ~OpenGLObject() {}
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
};
