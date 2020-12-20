#pragma once

#include <core/Renderer.hpp>
#include <core/gl/ShaderProgram.hpp>
#include <core/gl/VertexArray.hpp>
#include <core/gl/VertexBuffer.hpp>
#include <core/gl/IndexBuffer.hpp>
#include <core/gl/Texture.hpp>
#include <core/math/Transform2D.hpp>

class TransformationsRenderer : public Renderer
{
public:
    virtual bool onInit() override;
    virtual void onDestroy() override;
    virtual void onUpdate(double time) override;
    virtual void onDraw() override;
private:
    ShaderProgram* m_shader = nullptr;
    VertexArray* m_vertexArray = nullptr;
    VertexBuffer* m_vertexBuffer = nullptr;
    IndexBuffer* m_indexBuffer = nullptr;
    Texture* m_texture = nullptr;
    Transform2D m_transform;

    int m_modelMatrixUniformLocation = -1;
    int m_textureUniformLocation = -1;
};
