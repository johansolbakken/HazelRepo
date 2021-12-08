#version 330 core

layout (location = 0) in vec3 pos;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(pos, 1.0);
    vertexColor = vec4(pos.x, pos.y, clamp(1.0-pos.z, 0.0, 1.0), 1.0);
}
