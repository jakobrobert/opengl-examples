#pragma once

class OpenGLObject
{
public:
    virtual ~OpenGLObject() {}
    virtual void bind() = 0;
    virtual void unbind() = 0;
};
