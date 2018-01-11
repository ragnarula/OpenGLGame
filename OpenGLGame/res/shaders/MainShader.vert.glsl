#version 440

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iColour;
layout (location = 2) in vec3 iNormal;
layout (location = 3) in vec2 iUV;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 Normal;

out vec4 VertexColour;
out vec4 EyePosition;
out vec3 EyeNormal;
out vec2 UV;

void main()
{
	VertexColour = vec4(iColour, 1.0);
	EyePosition = MV * vec4(iPosition, 1.0);
	EyeNormal = normalize(Normal * iNormal);
	UV = iUV;
	gl_Position = MVP * vec4(iPosition, 1.0);
}