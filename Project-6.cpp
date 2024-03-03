#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include <iostream>
#include <limits>
#include <GL/freeglut_std.h>

// Function prototypes
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void do_movement();
void moveLighting(GLFWwindow *window);
int getUserInput();

// Window settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int shininess = 256; // Initial shininess value

// Camera settings
glm::vec3 cameraPos = glm::vec3(-1.12255f, -0.00404159f, 2.48081f);
glm::vec3 cameraFront = glm::vec3(0.0f, 2.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Camera rotation parameters
GLfloat yaw = -64.5f;
GLfloat pitch = 3.5f;

// Keyboard input buffer
bool keys[1024];

// Timing variables
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Light position
glm::vec3 lightPos(0.5f, 0.0f, 2.0f);

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create GLFW window
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Project 6", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Create shaders
    Shader cubeShader("Cube.vs", "Cube.frag");
    Shader lightCubeShader("Cube-Light.vs", "Cube-Light.frag");

    // Vertex data for cube
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

    // Set up vertex data and buffers
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // Set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // Set normal attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Light cube VAO (same as cube VAO)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        do_movement();
        moveLighting(window);

        // Rendering
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use lighting shader
        cubeShader.use();
        // Set shader uniforms
        cubeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        cubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        cubeShader.setVec3("lightPos", lightPos);
        cubeShader.setVec3("viewPos", cameraPos);
        GLint shininessLocation = cubeShader.getUniformLocation("shininess");
        if (shininessLocation == -1)
        {
            std::cerr << "Failed to locate the shininess uniform in the shader program!" << std::endl;
        }

        // Set the default value of shininess
        glUniform1i(shininessLocation, shininess);

        // Check if the user wants to change the value of shininess
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            int userInput = getUserInput();
            std::cout << "User input: " << userInput << std::endl;
            // Change the value of shininess based on user input
            shininess = userInput;
        }

        // View/Projection transformations
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(45.0f, (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 100.0f);
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);

        // World transformation
        glm::mat4 model = glm::mat4(1.0f);
        cubeShader.setMat4("model", model);

        // Render the cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Use light cube shader
        lightCubeShader.use();
        // Set shader uniforms
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightCubeShader.setMat4("model", model);

        // Draw light cube
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Swap buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    // De-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    // Terminate GLFW, clearing all previously allocated GLFW resources
    glfwTerminate();
    return 0;
}

// Framebuffer resize callback function
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // Resize viewport
    glViewport(0, 0, width, height);
}

// Keyboard callback function
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    // Handle escape key to close window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    // Store keyboard state
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

// Process keyboard input for camera movement
void do_movement()
{
    // Camera controls
    GLfloat rotationSpeed = 1.5f; // camera rotation speed
    GLfloat cameraSpeed = 0.025f; // camera movement speed

    // Reset camera position
    if (keys[GLFW_KEY_1])
    {
        cameraPos = glm::vec3(-1.12255f, -0.00404159f, 2.48081f);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        yaw = -64.5f;
        pitch = 3.5f;
        lightPos = glm::vec3(0.5f, 0.0f, 2.0f);
    }

    if (keys[GLFW_KEY_W]) // Move camera forward or backward using W and S
        cameraPos += cameraSpeed * cameraFront;
    if (keys[GLFW_KEY_S])
        cameraPos -= cameraSpeed * cameraFront;
    if (keys[GLFW_KEY_A]) // Move camera left or right using A and D
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (keys[GLFW_KEY_D])
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    // Move camera up with E key, down with Q
    if (keys[GLFW_KEY_E])
        cameraPos.y += cameraSpeed;
    if (keys[GLFW_KEY_Q])
        cameraPos.y -= cameraSpeed;

    // Rotate camera left or right using arrow keys
    if (keys[GLFW_KEY_LEFT])
        yaw -= rotationSpeed;
    if (keys[GLFW_KEY_RIGHT])
        yaw += rotationSpeed;

    // Rotate camera up or down using up and down arrow keys
    if (keys[GLFW_KEY_UP])
        pitch += rotationSpeed;
    if (keys[GLFW_KEY_DOWN])
        pitch -= rotationSpeed;

    // Constrain the pitch value to prevent screen flip
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Update cameraFront vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// Process keyboard input for moving the light source
void moveLighting(GLFWwindow *window)
{
    float lightSpeed = 0.5f;

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        lightPos.y += lightSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        lightPos.y -= lightSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        lightPos.x -= lightSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        lightPos.x += lightSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        lightPos.z += lightSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        lightPos.z -= lightSpeed * deltaTime;
}

// Get user input for shininess value
int getUserInput()
{
    int userInput;
    std::cout << "Please enter one of the following integer values (2, 4, 8, 16, 32, 64, 128, or 256): ";
    std::cin >> userInput;

    // Check if the input is within the desired range and is a valid value
    while (std::cin.fail() || (userInput != 2 && userInput != 4 && userInput != 8 && userInput != 16 &&
                               userInput != 32 && userInput != 64 && userInput != 128 && userInput != 256))
    {
        std::cout << "Invalid input. Please enter a valid integer value (2, 4, 8, 16, 32, 64, 128, or 256): ";
        std::cin.clear();                                                   // Clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard input buffer
        std::cin >> userInput;
    }

    return userInput;
}
