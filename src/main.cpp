#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include "shader.h"
#include "VAO.h"
#include "EBO.h"
#include "VBO.h"
#include "texture.h"

GLfloat vertices[] =
    {
        //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,           0.0f, 0.0f, // Lower left corner
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,            0.0f, 2.0f,  // Upper left corner
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,             2.0f, 2.0f,   // Upper right corner
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,            2.0f, 0.0f   // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
    {
        0, 2, 1, // Upper triangle
        0, 3, 2  // Lower triangle
};

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "demo", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "failed to open window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 800, 600);

    // GLuint VBO, VAO, EBO;
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0); //n3tiw location
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Shader shaderProgram("C:/Users/ROG/Desktop/openGl/vscode_cpp_opengl/build/shaders/default.vert", "C:/Users/ROG/Desktop/openGl/vscode_cpp_opengl/build/shaders/default.frag");
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    //scale uniform from vertex
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Texture
    //int widthTmg, heightImg, numColCh;
    //stbi_set_flip_vertically_on_load(true);
    //unsigned char *bytes = stbi_load("C:/Users/ROG/Desktop/openGl/vscode_cpp_opengl/src/textures/image.jpg", &widthTmg, &heightImg, &numColCh, 0);

    Texture image("C:/Users/ROG/Desktop/openGl/vscode_cpp_opengl/src/textures/image.jpg",GL_TEXTURE_2D,GL_TEXTURE0,GL_RGB,GL_UNSIGNED_BYTE);
    image.texUnit(shaderProgram,"tex0",0);
    //GLuint texture;
    //glGenTextures(1, &texture);
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, texture);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // float flatColor[] = {1.0f,1.0f,1.0f,1.0f};
    // glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,flatColor);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthTmg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    //glGenerateMipmap(GL_TEXTURE_2D);

    //stbi_image_free(bytes);
    //glBindTexture(GL_TEXTURE_2D, 0);

    //GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
    //shaderProgram.Activate();
    //glUniform1i(tex0Uni, 0);

    glClearColor(0.070588f, 0.062745f, 0.054902f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        // glUseProgram(shaderProgram);
        // glBindVertexArray(VAO);

        shaderProgram.Activate();

        glUniform1f(uniID, 0.5f);
        //glBindTexture(GL_TEXTURE_2D, texture);
        image.Bind();
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteProgram(shaderProgram);

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    image.Delete();
    //glDeleteTextures(1, &texture);
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}