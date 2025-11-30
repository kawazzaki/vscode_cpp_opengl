#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "shader.h"
#include "VAO.h"
#include "EBO.h"
#include "VBO.h"


int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = { // matrice a jemmi
       
        -0.5f, -0.288f, 0.0f, 
        0.5f, -0.288f, 0.0f,  
        0.0f, 0.577f, 0.0f,   

        
        -0.25f, 0.144f, 0.0f, 
        0.25f, 0.144f, 0.0f,  
        0.0f, -0.288f, 0.0f   
    };
    GLuint indices[] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1};

    GLFWwindow *window = glfwCreateWindow(800, 800, "demo", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "failed to open window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 640, 480);

    
    //GLuint VBO, VAO, EBO;
    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    //glBindVertexArray(VAO);

   // glBindBuffer(GL_ARRAY_BUFFER, VBO);
   // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    //glEnableVertexAttribArray(0); //n3tiw location
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    Shader shaderProgram("C:/Users/ROG/Desktop/openGl/demo/build/shaders/default.vert","C:/Users/ROG/Desktop/openGl/demo/build/shaders/default.frag");
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices,sizeof(vertices));
    EBO EBO1(indices,sizeof(indices));

    VAO1.LinkVBO(VBO1,0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(shaderProgram);
        //glBindVertexArray(VAO);
        
        shaderProgram.Activate();
        VAO1.Bind();

        
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    //glDeleteProgram(shaderProgram);

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}