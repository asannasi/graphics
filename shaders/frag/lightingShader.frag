#version 330 core

in vec3 normal;
in vec3 fragPos;

uniform vec3 color;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 fragColor;

void main(){
	vec3 lightDirection = normalize(lightPos - fragPos);
	vec3 norm = normalize(normal);
	fragColor = vec4(lightColor * color * max(dot(norm, lightDirection), 0.0f), 1.0f);
}