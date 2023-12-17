#version 420 core

layout (location = 0) in vec3 vPos;
layout (location = 1) inout vec3 vColor;

out vec3 color;

void main()
{
    gl_Position = vec4(vPos, 1.0);
    color = vColor;
}