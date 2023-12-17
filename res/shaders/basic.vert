#version 420 core

(layout = 0) in vec3 vPos;
(layout = 1) inout vec3 vColor;

void main()
{
    gl_Position = vPos;
}