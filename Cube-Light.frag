// Fragment shader for rendering the light source cube

#version 330 core
out vec4 FragColor; // Output color of the fragment shader

void main()
{
    // Set the color of the fragment to white (1.0 in all channels: red, green, blue, and alpha)
    FragColor = vec4(1.0); 
}