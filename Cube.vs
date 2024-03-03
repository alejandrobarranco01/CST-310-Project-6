#version 330 core

// Input attributes
layout (location = 0) in vec3 aPos; // Vertex position attribute
layout (location = 1) in vec3 aNormal; // Vertex normal attribute

// Output variables passed to the fragment shader
out vec3 FragPos;   // Fragment position in world coordinates
out vec3 Normal;    // Normal vector in world coordinates

// Uniform matrices for transformations
uniform mat4 model;      // Model matrix for object transformation
uniform mat4 view;       // View matrix for camera transformation
uniform mat4 projection; // Projection matrix for perspective transformation

void main()
{
    // Calculate the position of the fragment in world coordinates
    FragPos = vec3(model * vec4(aPos, 1.0));

    // Calculate the normal vector in world coordinates
    // Use the inverse transpose of the model matrix to preserve normal direction
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    
    // Apply transformations to the vertex position and set the output position
    gl_Position = projection * view * vec4(FragPos, 1.0);
}