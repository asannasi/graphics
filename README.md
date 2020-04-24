# Graphics Side Project

This project is meant to further my personal self-studying of computer 
graphics. Currently, it parses object files and displays static pointclouds 
after transforming them into clip space from model space. 

## How to run

This project uses openGL 3.3. It was developed in Visual Studio 2019 with 
the NuGet packages nupengl.core (which includes glew and glfw) and glm.
It was run on a Windows machine, so opengl32.lib was included in the 
dependencies and there is currently no OSX specific function support.

## How it works

1. The ObjFile and ShaderFile are used as RAII to get data from files.
1. The Object class is responsible for everything needed to render a object.
This includes the vertex buffers and modelToWorld matrix.
1. The Renderer class is responsible for rendering objects on the screen. It keeps
track of the view and projection matrices.
1. The Shaders class is responsible for setting up the shader program to use for rendering.
1. The main method sets up the window and has all the info on filenames. It also handles key presses.

## Resources

I'm following the [LearnOpenGL](https://learnopengl.com) tutorial and 
[this college class](https://cseweb.ucsd.edu/classes/wi20/cse167-a/). 
I tried my best to write my code from scratch with lots of comments
explaining each step to learn as much as possible.
