#include "PerspectiveCameraRenderer.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <cmath>

#include <core/Window.hpp>

bool PerspectiveCameraRenderer::onInit()
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

    m_camera.setFov(glm::radians(45.0f));
    m_camera.setNearPlane(0.1f);
    m_camera.setFarPlane(1000.0f);

    m_camera.setTranslation(glm::vec3(0.5f, 1.0f, 5.0f));
    m_camera.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));

    m_objectTransforms.emplace_back();
    m_objectTransforms.emplace_back();
    m_objectTransforms.emplace_back();

    m_elapsedTime = 0.0f;

    return true;
}

void PerspectiveCameraRenderer::onDestroy()
{
    // clean up: delete all opengl objects
    delete m_shader;
    delete m_vertexArray;
    delete m_vertexBuffer;
    delete m_indexBuffer;
    delete m_texture;
}

void PerspectiveCameraRenderer::onResize(int width, int height)
{
    glViewport(0, 0, width, height);

    float aspectRatio = (float)(width) / (float)(height);
    m_camera.setAspectRatio(aspectRatio);
}

void PerspectiveCameraRenderer::onUpdate(const Window& window, float frameTime)
{
    m_elapsedTime += frameTime;
    updateObjects();
    updateCamera(window, frameTime);
}

void PerspectiveCameraRenderer::onDraw()
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // draw all textured rectangles
    // binding and unbinding not necessary because resources stay the same, just to keep it more organized

    m_shader->use();
    m_vertexArray->bind();
    m_texture->bind(0);

    glUniform1i(m_textureUniformLocation, 0);

    glm::mat4 viewProjectionMatrix = m_camera.getViewProjectionMatrix();

    // draw all objects by applying the model matrix of the corresponding transform
    // actually drawing the same object multiple times, just with a different transform
    for (const auto& transform : m_objectTransforms) {
        glm::mat4 modelMatrix = transform.getModelMatrix();
        glm::mat4 mvpMatrix = viewProjectionMatrix * modelMatrix; // multiplication in reverse order
        glUniformMatrix4fv(m_mvpMatrixUniformLocation, 1, false, glm::value_ptr(mvpMatrix));
        glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);
    }
    
    m_shader->unuse();
    m_vertexArray->unbind();
    m_texture->unbind();
}

void PerspectiveCameraRenderer::updateObjects()
{
    glm::vec2 translation;
    translation.x = 0.75f * std::cos(3.0f * m_elapsedTime);
    translation.y = 0.75f * std::sin(2.0f * m_elapsedTime);
    m_objectTransforms[0].setTranslation(translation);

    translation.x += 0.5f;
    translation.y += 0.5f;
    m_objectTransforms[1].setTranslation(translation);

    translation.x += 1.0f;
    translation.y += 1.0f;
    m_objectTransforms[2].setTranslation(translation);

    glm::vec2 scale;
    scale.x = std::pow(2.0f, std::cos(3.0f * m_elapsedTime));
    scale.y = std::pow(2.0f, std::sin(2.0f * m_elapsedTime));
    m_objectTransforms[0].setScale(scale);

    scale *= 0.75f;
    m_objectTransforms[1].setScale(scale);

    scale *= 2.0f;
    m_objectTransforms[2].setScale(scale);

    float rotation = 2.0f * m_elapsedTime;
    m_objectTransforms[0].setRotation(rotation);

    rotation += 1.0f;
    m_objectTransforms[1].setRotation(rotation);

    rotation += 1.0f;
    m_objectTransforms[2].setRotation(rotation);
}

void PerspectiveCameraRenderer::updateCamera(const Window& window, float frameTime)
{
    updateCameraTranslation(window, frameTime);
    updateCameraRotation(window, frameTime);
}

void PerspectiveCameraRenderer::updateCameraTranslation(const Window& window, float frameTime)
{
    glm::vec3 translation = m_camera.getTranslation();
    float moveAmount = CAMERA_MOVE_SPEED * frameTime;

    if (window.getKey(GLFW_KEY_A) == GLFW_PRESS) {
        translation.x -= moveAmount;
    } else if (window.getKey(GLFW_KEY_D) == GLFW_PRESS) {
        translation.x += moveAmount;
    } else if (window.getKey(GLFW_KEY_S) == GLFW_PRESS) {
        translation.z += moveAmount;
    } else if (window.getKey(GLFW_KEY_W) == GLFW_PRESS) {
        translation.z -= moveAmount;
    } else if (window.getKey(GLFW_KEY_Q) == GLFW_PRESS) {
        translation.y -= moveAmount;
    } else if (window.getKey(GLFW_KEY_E) == GLFW_PRESS) {
        translation.y += moveAmount;
    }

    m_camera.setTranslation(translation);
}

void PerspectiveCameraRenderer::updateCameraRotation(const Window& window, float frameTime)
{
    glm::vec3 rotation = m_camera.getRotation();
    float rotationAmount = CAMERA_ROTATION_SPEED * frameTime;

    if (window.getKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
        rotation.y += rotationAmount;
    } else if (window.getKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
        rotation.y -= rotationAmount;
    } else if (window.getKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
        rotation.x -= rotationAmount;
    } else if (window.getKey(GLFW_KEY_UP) == GLFW_PRESS) {
        rotation.x += rotationAmount;
    }

    m_camera.setRotation(rotation);
}
