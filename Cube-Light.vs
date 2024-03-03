// Vertex shader for the light cube

#version 330 core
layout (location = 0) in vec3 aPos; //  The position of each vertex

// Uniform matrices for model, view, and projection transformations
uniform mat4 model; // Model matrix for object transformation
uniform mat4 view; // View matrix for camera position and orientation
uniform mat4 projection; // Projection matrix for perspective transformation

void main()
{
	// Calculate the final position of the vertex
    // Multiply the vertex position by the transformation matrices: projection, view, and model
    // The vertex position is transformed to clip space coordinates
    // The resulting position is stored in gl_Position, which is a built-in variable representing the final vertex position
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}