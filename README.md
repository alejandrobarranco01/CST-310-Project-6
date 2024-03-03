# Project 6: Specular Lighting, Objects, Illumination, and Shaders

### Authors

- Alejandro Barranco-Leyte
- Jason Broom

## Introduction

Project 6 focuses on exploring specular lighting, objects, illumination, and shaders using C++/OpenGL. The goal is to develop a program that visually demonstrates the impact of different shininess values on cubes rendered in a 3D environment.

## Contents

This submission should include the following files:

- Documentation file: Project-6.docx
- Code files:
  1. Cube-Light.frag
  2. Cube-Light.vs
  3. Cube.frag
  4. Cube.vs
  5. Project-6.cpp
  6. Shader.h

### Code Files

- [Cube-Light.frag](Cube-Light.frag)
- [Cube-Light.vs](Cube-Light.vs)
- [Cube.frag](Cube.frag)
- [Cube.vs](Cube.vs)
- [Project-6.cpp](Project-6.cpp)
- [Shader.h](Shader.h)

## Dependencies

The project relies on the following libraries and dependencies:

- OpenGL (for graphics rendering)
- GLUT (OpenGL Utility Toolkit)
- GLEW (OpenGL Extension Wrangler Library)
- GLFW (OpenGL Framework)
- SOIL (Simple OpenGL Image Library)
- GLM (OpenGL Mathematics)

Ensure that these libraries are installed on your system and linked properly during compilation to run the project successfully.

## Installation

To run the project, follow these steps:

1. Clone the repository from GitHub:
```bash
git clone https://github.com/alejandrobarranco01/CST-310-Project-6
```  
2. Navigate to the project directory:
```bash
cd CST-310-Project-6
```
3. Compile the project using the provided flags:
```bash
g++ -g Project-6.cpp -o Project-6 -lGL -lGLU -lglut -lGLEW -lglfw -lSOIL -lglm
```

## Running the Project
To run the project on Ubuntu terminal, use the following command:
```bash
./Project6
```
Ensure that you have the necessary libraries installed and linked properly to compile and run the project successfully.
