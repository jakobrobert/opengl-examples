#version 330 core

in vec3 v_color;
in vec2 v_textureCoord;

out vec4 FragColor;

uniform sampler2D u_texture;

void main()
{
    vec4 textureColor = texture(u_texture, v_textureCoord);
    // mix colors from texture and vertices by multiplying
    FragColor = textureColor * vec4(v_color, 1.0);
}
