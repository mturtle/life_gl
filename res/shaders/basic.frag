#version 420 core

(layout = 1) in vec3 color;

uniform vec3 overColor;

void main()
{
    gl_FragColor = vec4(color, 1.0);
}