#version 330 core

in vec3 normal;
in vec3 fragPos;

uniform vec3 viewerPos;
uniform vec3 color;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 fragColor;

void main(){
	vec3 norm = normalize(normal);
	vec3 diff = lightPos - fragPos;
	vec3 lightVec = normalize(diff);
	float attenuation = pow(1/length(diff), 2) * 0.001f;
	vec3 diffuse = attenuation * lightColor * (max(dot(norm, lightVec), 0.0f));

	vec3 viewVec = normalize(viewerPos - fragPos);
	vec3 reflectVec = reflect(-lightVec, norm);  
	vec3 specular = lightColor * (pow(max(dot(viewerPos, reflectVec), 0.0f), 128));

	fragColor = vec4(diffuse + specular, 1.0f);
}