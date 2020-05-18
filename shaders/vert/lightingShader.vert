#version 330 core

// Input is position vector at location 0
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normalIn;

uniform mat4 model;
uniform mat4 projView;

out vec3 normal;
out vec3 fragPos;

void main(){
	// Set position of current vertex and change coordinate spaces
	// Mutiply matrices right to left
	fragPos = vec3(model * vec4(vertex, 1.0));
	gl_Position = projView * vec4(fragPos, 1.0);
	normal = vec3(model * vec4(normalIn, 0.0f));
}