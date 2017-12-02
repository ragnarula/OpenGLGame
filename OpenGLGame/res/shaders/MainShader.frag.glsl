#version 440

uniform sampler2D Albedo;

in vec4 VertexColour;

out vec4 FragColor;

void main()
{
    FragColor = VertexColour;
}