#pragma once

#include <glad/glad.h>
#include <vector>


class ElementBuffer
{
public:

	// Genera un EBO (un buffer che esiste nella GPU) e copia gli indici che definiscono l'ordine di disegno dei vertici sull'EBO.
	ElementBuffer(std::vector<GLuint>& indices);

	// Libera le risorse GPU associate all' EBO
	~ElementBuffer();

	// Collega (bind) l'EBO, rendendolo attivo
	void Bind();

	// Scollega (unbind) l'EBO, rendendolo inattivo
	void Unbind();

private:

	GLuint ID; // Identificatore OpenGL dell'EBO
};

