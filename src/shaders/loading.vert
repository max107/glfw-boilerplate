#version 330 core

layout(location = 0) in vec2 vertexPosition_modelspace;

uniform mat4 mvp;
uniform vec2 position;

void main()
{
    gl_Position =  mvp * vec4(vertexPosition_modelspace + position, 0, 1);
}
