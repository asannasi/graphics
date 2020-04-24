#version 330 core

// Input is position vector at location 0
layout (location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(){
	// Set position of current vertex and change coordinate spaces
	// Mutiply matrices right to left
	gl_Position = proj * view * model * vec4(pos, 1.0);
}