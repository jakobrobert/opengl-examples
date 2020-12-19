#version 330 core

uniform mat4 u_modelMatrix;

in vec2 a_position;
in vec3 a_color;
in vec2 a_textureCoord;

out vec3 v_color;
out vec2 v_textureCoord;

void main()
{
    gl_Position = u_modelMatrix * vec4(a_position, 0.0, 1.0);
    v_color = a_color;
    v_textureCoord = a_textureCoord;
}
