#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>


// Rappresenta un singolo vertice con attributi per il rendering 
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VertexBuffer
{
public:

	// Genera un VBO (un buffer che esiste nella GPU) e copia i dati dei vertici sul VBO.
	VertexBuffer(std::vector<Vertex> &vertices);

	// Libera le risorse GPU associate al VBO
	~VertexBuffer();

	// Collega (bind) il VBO, rendendolo attivo
	void Bind();

	// Scollega (unbind) il VBO, rendendolo inattivo
	void Unbind();

private:

	GLuint ID; // Identificatore OpenGL del VBO
};
