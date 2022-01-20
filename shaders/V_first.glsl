#version 410

in vec3 position;
in vec3 color;
in vec3 normal;

out vec4 colorV;
flat out vec3 normalV;
out vec3 posV;

uniform mat4 mM;
uniform mat4 mV;
uniform mat4 mP;
uniform mat4 mMV;
uniform mat4 mMVP;
uniform mat4 mRm2w;

void main()
{
    normalV = mat3(mRm2w) * normal;
    colorV = vec4(color, 1.0);
    posV = vec3( mM * vec4(position,1.0));
    
    gl_Position = mMVP * vec4(position, 1.0);
    
}