#version 330 core

uniform sampler2D u_texture;

in vec3 v_color;
in vec2 v_textureCoord;

out vec4 FragColor;

void main()
{
    vec4 textureColor = texture(u_texture, v_textureCoord);
    // mix colors from texture and vertices by multiplying
    FragColor = textureColor * vec4(v_color, 1.0);
}
