#include <iostream>



#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>



#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem.h>
#include <display.h>
#include <shader.h>
#include <texture.h>
#include <camera.h>
#include <callback_setter.h>
#include <callback_handler.h>
#include <mesh.h>
#include <transform.h>


// timing
double deltaTime = 0.0f;	// time between current frame and last frame
double lastTime = 0.0f;


glm::vec3 newPos(glm::vec3 pos, double time);

int main()
{
    /*********************** Display ***********************/
    // Display object
    Display display("Transperineal Prostate Biopsy");

    // Window handle
    GLFWwindow* window = display.getWindowHandle(); 

    /******************* Set Callback Functions *******************/
    CallbackSetter callbackSet(window);
    CallbackHandler callbackHandler(window);
    callbackHandler.setCursorCoords((float)display.getWindowWidth() / 2.0f, 
        (float)display.getWindowHeight() / 2.0f);
    
    /*********************** Camera ***********************/
    // Camera object
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f); float cameraFOV = 45.0f;
    Camera camera(window, cameraPos, cameraFOV,
        display.getWindowWidth() / (float)display.getWindowHeight(),
        0.01f, 1000.0f);
    
    // Set camera callback inputs
    callbackHandler.setCamera(&camera);

    /*********************** Mesh ***********************/
    Mesh mesh("./resources/objects/cube/cube.obj", GL_STATIC_DRAW);
    std::vector<glm::vec3> meshVertices = mesh.getObjVerticesPos();

    /*********************** Shader ***********************/
    // Shader object
    Shader objectShader("share/simpleShader");
    Shader lightShader("share/lightShader");

    /*********************** Transformation ***********************/
    Transform objectTransform;
    Transform lightTransform;

    /*********************** Texture ***********************/
    Texture texture("./resources/objects/cube/cube.png");
    objectShader.bind();

    /*********************** Lighting ***********************/
    glm::vec3 lightPos = glm::vec3(3.0f, 3.0f, 10.0f);

    /*********************** Render Loop ***********************/
    while (!display.isClosed())
    {
        // Time tracking
        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Clear display background
        display.clear(0.5, 0.5, 0.5);

        /**************** Camera ****************/
        // Update camera 
        camera.update(deltaTime);

        /**************** Object ****************/
        // Bind shader 
        objectShader.bind();

        // Camera and light position
        objectShader.setVec3("viewPos", camera.getCameraPosition());
        objectShader.setVec3("light.position", lightPos);

        // Light properties
        objectShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f); 
        objectShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        objectShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // Material properties
        objectShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        objectShader.setFloat("material.shininess", 64.0f);

        // View and projection
        objectShader.setMat4("projection", camera.getProjection());
        objectShader.setMat4("view", camera.getView());

        // Model transform 
        objectTransform.setRot(glm::vec3(0.0, 0.0f, 0.0f));
        objectTransform.setPos(glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 model = objectTransform.getModel();
        objectShader.setMat4("model", model);

        // Bind texture 
        texture.bind(0);

        // Draw mesh
        std::vector<glm::vec3> newMeshVertices(mesh.getObjVerticesNum());

        newMeshVertices = meshVertices;

        for (uint i = 0; i < meshVertices.size(); i = i + 2)
        {
            newMeshVertices.at(i) = newPos(meshVertices.at(i), currentTime);
        }


        mesh.setObjVerticesPos(newMeshVertices);


        mesh.draw();

        // Update display
        display.update();

        // Poll events
        glfwPollEvents();
    }

    return 0;
}

glm::vec3 newPos(glm::vec3 pos, double time)
{
    // Deformation amplitude and frequency 
    float amp = 1.5f; float freq = 1.0f; 
    float mul = amp * sin(2.0f * M_PI * freq * (float)time);

    glm::vec3 normal_pos = glm::normalize(pos);
    glm::vec3 out_vec = mul * normal_pos;
    return out_vec;
}

