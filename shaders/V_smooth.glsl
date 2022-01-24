#version 410

in vec3 position;
in vec3 normal;
in vec2 texco;

out vec3 normalF;
out vec3 positionF;
out vec2 texcoF;

uniform mat4 mM;
uniform mat4 mV;
uniform mat4 mP;
uniform mat4 mMV;
uniform mat4 mMVP;
uniform mat4 mRm2w;

void main()
{
    normalF = mat3(mRm2w) * normal;
    positionF = vec3( mM * vec4(position,1.0));
    texcoF = vec2(0,0);
    gl_Position = mMVP * vec4(position, 1.0);
    
}