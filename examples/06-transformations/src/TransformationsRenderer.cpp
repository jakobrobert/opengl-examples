#include "TransformationsRenderer.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

bool TransformationsRenderer::onInit()
{
    // create shader
    std::string shaderFilename = "assets/shaders/texture_and_vertex_color";
    m_shader = new ShaderProgram(shaderFilename + ".vert", shaderFilename + ".frag");
    // get uniform locations
    m_modelMatrixUniformLocation = m_shader->getUniformLocation("u_modelMatrix");
    m_textureUniformLocation = m_shader->getUniformLocation("u_texture");

    // create vertex array
    m_vertexArray = new VertexArray();
    m_vertexArray->bind();

    // create vertex buffer 
    float vertices[] = {
        // counter-clockwise order
        // position         color           texture coord
        -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // left bottom, red
        0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // right bottom, green
        0.5f, 0.5f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // right top, blue
        -0.5f, 0.5f,    1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // left top, yellow
    };
    m_vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
    // connect vertex buffer to vertex array
    m_vertexBuffer->bind();

    // specify vertex layout
    VertexLayout layout;
    layout.addAttribute(m_shader->getAttributeLocation("a_position"), 2);
    layout.addAttribute(m_shader->getAttributeLocation("a_color"), 3);
    layout.addAttribute(m_shader->getAttributeLocation("a_textureCoord"), 2);
    // connect vertex layout to vertex array
    m_vertexArray->setVertexLayout(layout);

    // create index buffer
    unsigned int indices[6] {
        // counter-clockwise order
        0, 1, 2,    // right bottom triangle
        2, 3, 0     // left top triangle
    };
    m_indexBuffer = new IndexBuffer(indices, 6);
    // connect index buffer to vertex array
    m_indexBuffer->bind();
    
    // unbind objects to leave a clean state
    m_vertexArray->unbind();
    m_vertexBuffer->unbind();
    m_indexBuffer->unbind();

    // create texture
    m_texture = new Texture("assets/textures/awesome_face.png");

    // black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // enable alpha blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void TransformationsRenderer::onDestroy()
{
    // clean up: delete all opengl objects
    delete m_shader;
    delete m_vertexArray;
    delete m_vertexBuffer;
    delete m_indexBuffer;
    delete m_texture;
}

void TransformationsRenderer::onUpdate(double time)
{
    glm::vec2 translation;
    translation.x = 0.75 * (float)(std::cos(3.0 * time));
    translation.y = 0.75 * (float)(std::sin(2.0 * time));
    m_transform.setTranslation(translation);

    glm::vec2 scale;
    scale.x = (float)(std::pow(2.0, std::cos(3.0 * time)));
    scale.y = (float)(std::pow(2.0, std::sin(2.0 * time)));
    m_transform.setScale(scale);

    float rotation = (float)(2.0 * time);
    m_transform.setRotation(rotation);
}

void TransformationsRenderer::onDraw()
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // draw the textured rectangle
    // binding and unbinding not necessary because they are the same objects each time
    // just to keep it more organized, easier to extend
    m_shader->use();
    m_vertexArray->bind();
    m_texture->bind(0);
    glUniform1i(m_textureUniformLocation, 0);
    glm::mat4 modelMatrix = m_transform.getModelMatrix();
    glUniformMatrix4fv(m_modelMatrixUniformLocation, 1, false, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);
    m_shader->unuse();
    m_vertexArray->unbind();
    m_texture->unbind();
}
