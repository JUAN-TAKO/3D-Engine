#version 410

in vec3 positionF;
in vec3 normalF;
in vec2 texcoF;

out vec4 outColor;

uniform mat4 mM;
uniform mat4 mV;
uniform mat4 mP;
uniform mat4 mMV;
uniform mat4 mMVP;
uniform mat4 mRm2w;

struct Light{
    vec3 direction;
    vec3 color;
    float ambiant;
};

uniform Light light;

void main()
{
    vec4 ambiant = vec4(1)*vec4(light.color,1)*light.ambiant;

    float diff = max(dot(normalF, light.direction), 0.0);
    vec4 diffuse = vec4(1)*vec4(diff*light.color, 1);
    diffuse *= (1-light.ambiant);

    outColor = ambiant + diffuse;
}