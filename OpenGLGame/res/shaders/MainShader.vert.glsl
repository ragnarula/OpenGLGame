#version 440

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iColour;
layout (location = 2) in vec3 iNormal;
layout (location = 3) in vec2 iUV;

struct LightInfo
{
	vec3 Colour;
    vec3 Position;
	vec3 Direction;
};

layout (std430, binding = 1) buffer LightsBuffer {
    LightInfo Lights[16];
};

uniform uint NumLights;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 Normal;

out vec4 VertexColour;

void main()
{
	VertexColour = vec4(iColour, 1.0);
	gl_Position = MVP * vec4(iPosition, 1.0);
}