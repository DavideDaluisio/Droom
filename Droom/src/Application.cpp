#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Test", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 800);


    Shader shader("src/Shaders/vertexShader.vs", "src/Shaders/fragmentShader.fs");
    // Definizione dei vertici in formato compatibile con la classe VertexBuffer
    std::vector<Vertex> vertices = {
        {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // Vertice 0
        {glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // Vertice 1
        {glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // Vertice 2
        {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)}  // Vertice 3
    };

    // Indici per disegnare i triangoli
    std::vector<GLuint> indices = {
        0, 1, 2,
        0, 2, 3
    };

    VertexArray VAO1;
    VAO1.Bind();

    VertexBuffer VBO1(vertices);
    ElementBuffer EBO1(indices);

    // Configurazione degli attributi nel VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0); // Posizione
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color)); // Colore


    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader.GetID());
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
