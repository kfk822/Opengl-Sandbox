#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 objectColor;
uniform vec3 ligthColor;
uniform vec3 ligthPos;
uniform vec3 viewPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vec3 Normal = mat3(transpose(inverse(model)))* aNormal;
    vec3 FragPos = vec3(model * vec4(aPos,1.0));

    float ambientStrength =0.1;
    vec3 ambient = ambientStrength * ligthColor;

    vec3 norm = normalize(Normal);
    vec3 ligthDir = normalize(ligthPos - FragPos);

    float diff = max(dot(norm,ligthDir),0.0);
    vec3 diffuse = diff * ligthColor;
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-ligthDir,norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * ligthColor;

    color = (ambient + diffuse + specular) * objectColor;
}       