#version 330 core
out vec4 FragColor;

uniform vec3 ligthColor;

void main(){
    FragColor = vec4(ligthColor,1.0);
}