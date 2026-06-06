#version 330 core
struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
struct Ligth{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;  

uniform vec3 viewPos;
uniform Material material;
uniform Ligth ligth;


void main()
{
    vec3 ambient = material.ambient * ligth.ambient;

    vec3 norm = normalize(Normal);
    vec3 ligthDir = normalize(ligth.position - FragPos);
    float diff = max(dot(norm,ligthDir),0.0);
    vec3 diffuse = (material.diffuse * diff) * ligth.diffuse;
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-ligthDir,norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = (material.specular * spec) * ligth.specular;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}