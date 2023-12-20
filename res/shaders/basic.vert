#version 420 core

layout (location = 0) in vec3 vPos;
layout (location = 1) inout vec3 vColor;

out vec3 color;

uniform mat4 mvp;

float rand(int seed)
{
    return fract(sin(float(seed) * 12.9898) * 43758.5453);
}

void main()
{
    gl_Position = mvp * vec4(vPos, 1.0);
    color = vec3(rand(gl_VertexID), rand(gl_VertexID + 23), rand(gl_VertexID + 42));
    gl_PointSize = 8.0;
}