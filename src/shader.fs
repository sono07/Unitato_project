#version 330 core

in vec2 vUVs;
in vec3 vNormals;
in vec3 vFragPos;

uniform sampler2D uTexture;
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uViewPos;

out vec4 outColor;

void main()
{
    float ambientIntensity = 0.15f;
    float specularIntensity = 0.5f;
    vec3 ambientColor = {1.0f, 1.0f, 1.0f};

    vec3 ambientComponent = ambientIntensity * ambientColor;

    vec3 lightDir = normalize(uLightPos - vFragPos);
    float diffuseIntensity = max(dot(vNormals, lightDir), 0.0f);
    vec3 diffuseComponent = diffuseIntensity * uLightColor;

    vec3 viewDir = normalize(uViewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, vNormals);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 16.0f);
    vec3 specularComponent = specularIntensity * spec * uLightColor;

    vec3 result = ambientComponent + diffuseComponent + specularComponent;

    outColor = vec4(result, 1.0f) * texture(uTexture, vUVs);
    //outColor = vec4(1.0f, 0.2f, 0.5f, 1.0f);
} 