#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "dependencies/imgui/imgui.h"
#include "dependencies/imgui/imgui_impl_glfw.h"
#include "dependencies/imgui/imgui_impl_opengl3.h"

#include "common/Shader.h"
#include "common/Camera.h"
#include "common/OpenGLUtils.h"
#include "common/WindowManager.h"
#include "common/ImGuiManager.h"
#include "common/VertexBuffer.h"
#include "common/IndexBuffer.h"


int main()
{
    OpenGLInit init;
    WindowManager windowManager(&init); 
    ImGuiManager imguiManager;
    auto window = windowManager.CreateWindow(3840, 2160, "Graphics Engine", NULL, NULL);

    imguiManager.Init(window.get()); 
    Camera cam = camera(window.get());  

    static const float s_VertexBufferDataCube[] = {
        -1.0f,-1.0f,-1.0f, 
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f, 
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, 
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    static const unsigned int s_IndexBufferDataCube[] = { 
    0, 1, 2,   // Triangle 1
    3, 4, 5,   // Triangle 2
    6, 7, 8,   // Triangle 3
    9, 10, 11, // Triangle 4
    12, 13, 14,// Triangle 5
    15, 16, 17,// Triangle 6
    18, 19, 20,// Triangle 7
    21, 22, 23,// Triangle 8
    24, 25, 26,// Triangle 9
    27, 28, 29,// Triangle 10
    30, 31, 32,// Triangle 11
    33, 34, 35 // Triangle 12
    };


    static const float s_ColorBufferData[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
    };

    unsigned int VertexArrayID{};
    glGenVertexArrays(1, &VertexArrayID);   
    glBindVertexArray(VertexArrayID);   

    VertexBuffer vertexBuffer(s_VertexBufferDataCube, sizeof(s_VertexBufferDataCube));
    VertexBuffer vertexBufferTriangle(s_VertexBufferDataCube, sizeof(s_VertexBufferDataCube)); 
    VertexBuffer vertexBufferSquareTwo(s_VertexBufferDataCube, sizeof(s_VertexBufferDataCube));

    IndexBuffer indexBufferSquareOne(s_IndexBufferDataCube, sizeof(s_IndexBufferDataCube)); 
    IndexBuffer indexBufferTriangle(s_IndexBufferDataCube, sizeof(s_IndexBufferDataCube)); 
    IndexBuffer indexBufferSquareTwo(s_IndexBufferDataCube, sizeof(s_IndexBufferDataCube)); 

    
    uint32_t colorbuffer{}; 
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(s_ColorBufferData), s_ColorBufferData, GL_STATIC_DRAW); 

    uint32_t programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader"); 

    glm::vec3 translateSquareOne(-3.0f, 0.0f, 0.0f); 
    glm::vec3 translateSquareTwo(6.0f, 0.0f, 0.0f);
    glm::vec3 translateTriangle(2.0f, 0.0f, 0.0f); 

    do {

        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);
        int width, height; 

        glfwGetFramebufferSize(window.get(), &width, &height); 

        uint32_t MatrixIDS = glGetUniformLocation(programID, "MVP");  

        cam.Controls(window.get()); 
        cam.GetProjectionMatrix();
        cam.GetViewMatrix();
        imguiManager.RenderUI(cam, window.get(), translateSquareOne, translateSquareTwo, translateTriangle);


        // creates a model matrix. This matrix is used to position, 
        // scale, and rotate objects in the world. By default, it's the identity matrix (1.0f), 
        // which means no transformation. If you wanted to move or rotate your object, you would modify this matrix.
        glm::mat4 ModelSquareOne = glm::mat4(1.0f);
        ModelSquareOne = glm::translate(ModelSquareOne, translateSquareOne);
        glm::mat4 MVPOne = cam.GetProjectionMatrix() * cam.GetViewMatrix() * ModelSquareOne; // Combine them into the MVP matrix      

        // Get the location of the MVP uniform
        glm::mat4 ModelTriangle = glm::mat4(1.0f);
        ModelTriangle = glm::translate(ModelTriangle, translateTriangle);
        glm::mat4 MVPTwo = cam.GetProjectionMatrix() * cam.GetViewMatrix() * ModelTriangle; // Combine them into the MVP matrix     

        glm::mat4 ModelSquareTwo = glm::mat4(1.0f);
        ModelSquareTwo = glm::translate(ModelSquareTwo, translateSquareTwo);
        glm::mat4 MVPThree = cam.GetProjectionMatrix() * cam.GetViewMatrix() * ModelSquareTwo; // Combine them into the MVP matrix   

        glEnableVertexAttribArray(0); // position  
        glEnableVertexAttribArray(1); // color  

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
        vertexBuffer.Bind(); 
        indexBufferSquareOne.Bind(); 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);  
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);  
          

        glUniformMatrix4fv(MatrixIDS, 1, GL_FALSE, glm::value_ptr(MVPOne));  
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);  

        glUniformMatrix4fv(MatrixIDS, 1, GL_FALSE, glm::value_ptr(MVPTwo)); 
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); 

        glUniformMatrix4fv(MatrixIDS, 1, GL_FALSE, glm::value_ptr(MVPThree));  
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); 

        glDisableVertexAttribArray(0); 
        glDisableVertexAttribArray(1);

        // Swap buffers 
        glfwSwapBuffers(window.get());
        glfwPollEvents();

        //Enabled so gpu cant render inside of the cubes
        //glEnable(GL_CULL_FACE); 
        //glfwSwapInterval(0); // Disable V-Sync

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window.get()) == 0);
}

