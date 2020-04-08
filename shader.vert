#version 330 core

// Input is position vector at location 0
layout (location = 0) in vec3 pos;

void main(){
	// Set position of current vertex
	gl_Position = vec4(pos, 1.0);
}