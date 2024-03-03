#version 330 core
out vec4 FragColor; // // Output color of the fragment shader

in vec3 Normal;  // Input normal vector from the vertex shader
in vec3 FragPos;   // Input fragment position from the vertex shader
  
uniform vec3 lightPos;     // Position of the light source
uniform vec3 viewPos;      // Position of the viewer (camera)
uniform vec3 lightColor;   // Color of the light source
uniform vec3 objectColor;  // Color of the object being rendered

uniform int shininess; // Shininess of the material for specular reflection

void main()
{
    // Ambient Lighting
    float ambientStrength = 0.1; // Set the ambient lighting strength
    vec3 ambient = ambientStrength * lightColor; // Calculate ambient light contribution
  	
    // Diffuse Lighting
    vec3 norm = normalize(Normal); // Normalize the normal vector
    vec3 lightDir = normalize(lightPos - FragPos); // Calculate direction from the fragment to the light source
    float diff = max(dot(norm, lightDir), 0.0); // Compute the diffuse reflection factor
    vec3 diffuse = diff * lightColor; // Calculate diffuse light contribution
    
    // Specular Lighting
    float specularStrength = 0.5; // Set the specular lighting strength
    vec3 viewDir = normalize(viewPos - FragPos); // Calculate the direction to the viewer
    vec3 reflectDir = reflect(-lightDir, norm);  // Calculate the reflection direction
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); // Compute the specular reflection factor
    vec3 specular = specularStrength * spec * lightColor;  // Calculate specular light contribution
    
    // Combine Ambient, Diffuse, and Specular Lighting
    vec3 result = (ambient + diffuse + specular) * objectColor; // Combine the lighting components with the object color
     
    // Output the final fragment color
    FragColor = vec4(result, 1.0);
} 