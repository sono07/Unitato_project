#version 330 core

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inUVs;
layout (location = 2) in vec3 inNormals;

out vec2 vUVs;
out vec3 vNormals;
out vec3 vFragPos;

void main()
{
    gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(inPos.x, inPos.y, inPos.z, 1.0);
    vFragPos = vec3(uModelMatrix * vec4(inPos.x, inPos.y, inPos.z, 1.0));
    vUVs = inUVs;
    vNormals = normalize(inNormals);
}