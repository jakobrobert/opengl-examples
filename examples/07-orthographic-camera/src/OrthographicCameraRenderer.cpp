#include "OrthographicCameraRenderer.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <core/Window.hpp>

bool OrthographicCameraRenderer::onInit()
{
    // create shader
    std::string shaderFilename = "assets/shaders/texture_and_vertex_color";
    m_shader = new ShaderProgram(shaderFilename + ".vert", shaderFilename + ".frag");
    // get uniform locations
    m_mvpMatrixUniformLocation = m_shader->getUniformLocation("u_mvpMatrix");
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
    layout.enableAttributes();

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

    m_camera.setTranslation(glm::vec2(1.0f, 0.5f));
    m_camera.setScale(glm::vec2(2.0f, 2.0f));
    m_camera.setRotation(glm::radians(0.0f));

    m_elapsedTime = 0.0f;

    return true;
}

void OrthographicCameraRenderer::onDestroy()
{
    // clean up: delete all opengl objects
    delete m_shader;
    delete m_vertexArray;
    delete m_vertexBuffer;
    delete m_indexBuffer;
    delete m_texture;
}

void OrthographicCameraRenderer::onResize(int width, int height)
{
    glViewport(0, 0, width, height);

    float aspectRatio = (float)(width) / (float)(height);
    m_camera.setViewportSize(glm::vec2(2.0f * aspectRatio, 2.0f));
}

void OrthographicCameraRenderer::onUpdate(const Window& window, float frameTime)
{
    m_elapsedTime += frameTime;
    updateObject(window);
    updateCamera(window, frameTime);
}

void OrthographicCameraRenderer::onDraw()
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
    glm::mat4 viewMatrix = m_camera.getViewMatrix();
    glm::mat4 projectionMatrix = m_camera.getProjectionMatrix();
    // calculate mvp (model view projection) matrix by combining the matrices
    // multiplication order is reverse of transformation order
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    glUniformMatrix4fv(m_mvpMatrixUniformLocation, 1, false, glm::value_ptr(mvpMatrix));

    glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

    m_shader->unuse();
    m_vertexArray->unbind();
    m_texture->unbind();
}

void OrthographicCameraRenderer::updateObject(const Window& window)
{
    glm::vec2 translation;
    translation.x = 0.75f * std::cos(3.0f * m_elapsedTime);
    translation.y = 0.75f * std::sin(2.0f * m_elapsedTime);
    m_transform.setTranslation(translation);

    glm::vec2 scale;
    scale.x = std::pow(2.0f, std::cos(3.0f * m_elapsedTime));
    scale.y = std::pow(2.0f, std::sin(2.0f * m_elapsedTime));
    m_transform.setScale(scale);

    float rotation = 2.0f * m_elapsedTime;
    m_transform.setRotation(rotation);
}

void OrthographicCameraRenderer::updateCamera(const Window& window, float frameTime)
{
    updateCameraTranslation(window, frameTime);
    updateCameraRotation(window, frameTime);
    updateCameraScale(window, frameTime);
}

void OrthographicCameraRenderer::updateCameraTranslation(const Window& window, float frameTime)
{
    glm::vec2 translation = m_camera.getTranslation();
    float moveAmount = CAMERA_MOVE_SPEED * frameTime;

    if (window.getKey(GLFW_KEY_A) == GLFW_PRESS) {
        translation.x -= moveAmount;
    } else if (window.getKey(GLFW_KEY_D) == GLFW_PRESS) {
        translation.x += moveAmount;
    } else if (window.getKey(GLFW_KEY_S) == GLFW_PRESS) {
        translation.y -= moveAmount;
    } else if (window.getKey(GLFW_KEY_W) == GLFW_PRESS) {
        translation.y += moveAmount;
    }
    
    m_camera.setTranslation(translation);
}

void OrthographicCameraRenderer::updateCameraRotation(const Window& window, float frameTime)
{
    float rotation = m_camera.getRotation();
    float rotationAmount = CAMERA_ROTATION_SPEED * frameTime;

    if (window.getKey(GLFW_KEY_Q) == GLFW_PRESS) {
        rotation += rotationAmount;
    } else if (window.getKey(GLFW_KEY_E) == GLFW_PRESS) {
        rotation -= rotationAmount;
    }

    m_camera.setRotation(rotation);
}

void OrthographicCameraRenderer::updateCameraScale(const Window& window, float frameTime)
{
    float scale = m_camera.getScale().x;
    float scaleAmount = CAMERA_SCALE_SPEED * frameTime;

    if (window.getKey(GLFW_KEY_Z) == GLFW_PRESS) {
        scale -= scaleAmount;
    } else if (window.getKey(GLFW_KEY_X) == GLFW_PRESS) {
        scale += scaleAmount;
    }

    m_camera.setScale(glm::vec2(scale, scale));
}
