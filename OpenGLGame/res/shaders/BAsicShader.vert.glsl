#version 400

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;

out vec2 texcoord;
out vec3 norm;
out vec4 p;

void main()
{
	norm = normalize(normalMatrix * a_normal);
	p = modelViewMatrix * vec4(a_position, 1.0);
	gl_Position = projectionMatrix * p;
	texcoord = a_texcoord;
}