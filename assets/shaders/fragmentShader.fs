#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;  

uniform vec3 objectColor;
uniform vec3 ligthColor;
uniform vec3 ligthPos;
uniform vec3 viewPos;


void main()
{
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

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}