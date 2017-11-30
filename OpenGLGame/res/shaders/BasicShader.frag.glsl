#version 400

uniform vec3 lightPos;
uniform sampler2D sampler0;

in vec2 texcoord;
smooth in vec3 norm;
smooth in vec4 p;

out vec4 fragColour;

void main()
{
    vec3 dx = dFdx(p.xyz);
    vec3 dy = dFdy(p.xyz);

    vec3 norm2 = normalize(cross(dx, dy));

    vec3 La = vec3(1.0);
    vec3 Ld = vec3(1.0);
    vec3 Ls = vec3(1.0);

    vec3 Ma = vec3(0.6);
    vec3 Md = vec3(1.0);
    vec3 Ms = vec3(0.1);

    float shininess = 10;

    vec3 s = normalize(lightPos - p.xyz);
    vec3 r = reflect(-s, norm2);
    vec3 v = normalize(-p.xyz);
    vec3 ambient = La * Ma;
    float sDotN = max(dot(s, norm2), 0.0);

    vec3 diffuse = Ld * Md * sDotN;
    vec3 specular = vec3(0.0f);

    if (sDotN > 0.0f) {
        specular = Ls * Ms * pow(max(dot(r, v), 0.0), shininess);
    }

	fragColour = vec4(0.2, 0.8, 0.0, 1.0) * vec4(ambient + diffuse + specular, 1.0);
	//fragColour = texture(sampler0, texcoord) * vec4(ambient + diffuse + specular, 1.0);
	//fragColour = vec4(1.0, 0.0, 0.0, 1.0);

    // https://stackoverflow.com/questions/21079623/how-to-calculate-the-normal-matrix
	//fragColour.rgb = normalize(norm) * 0.5 + 0.5;
	//fragColour.a = 1.0;
}