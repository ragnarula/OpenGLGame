#version 440

uniform sampler2D DiffuseMap;
uniform sampler2D NormalMap;
uniform bool UseDiffuse;
uniform bool UseNormal;
uniform vec4 ADSSh;
uniform uint NumLights;

struct LightInfo
{
	vec4 Colour;
    vec4 Position;
	vec4 Direction;
};

layout (std430, binding = 1) buffer LightsBuffer {
    LightInfo Lights[16];
};


in vec4 VertexColour;
in vec4 EyePosition;
in vec3 EyeNormal;
in varying vec2 UV;

out vec4 FragColor;

vec3 ads(int LightNumber, vec4 Position, vec3 Normal)
{
	vec3 s = vec3(Lights[LightNumber].Position - Position);
	float d = length(s);
	d = d * d;
	s = normalize(s);

	float l = max(dot(s, Normal), 0.0);

	vec3 Diffuse = (ADSSh.y * l * Lights[LightNumber].Colour.xyz) * 200 / d;
	vec3 Specular;
	
	if (l > 0.0)
	{
		vec3 v = normalize(vec3(-Position));
		vec3 h = normalize(s + v);
		Specular = (ADSSh.z * pow(max(dot(h, Normal), 0.0), ADSSh.w) * Lights[LightNumber].Colour.xyz) * 200 / d;
	}
	
	return ADSSh.x + Diffuse + Specular;
}

void main()
{
	vec3 LightColour = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < NumLights; i++)
	{
		LightColour += ads(i, EyePosition, EyeNormal);
	}

	vec4 SurfaceColour;

	if(UseDiffuse)
	{
		SurfaceColour = texture(DiffuseMap, UV);
	}
	else
	{
		SurfaceColour = VertexColour;
	}

	vec4 LinearColour = SurfaceColour * vec4(LightColour, 1.0);
	vec4 GammaCorrectedColour = vec4(pow(LinearColour.xyz, vec3(1.0/2.2)), LinearColour.w);
    FragColor = GammaCorrectedColour;
    //FragColor = texture(DiffuseMap, UV);
}