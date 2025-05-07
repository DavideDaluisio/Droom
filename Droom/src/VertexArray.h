#pragma once

#include <glad/glad.h>

#include "VertexBuffer.h"

class VertexArray
{
public:

	// Genera un VAO che memorizza lo stato di configurazione degli attributi dei vertici
	VertexArray();

	// Libera le risorse GPU associate al VBO
	~VertexArray();

	// Collega un attributo di vertice al VAO specificando come leggere i dati dal VBO
	void LinkAttrib(VertexBuffer& VertexBuffer, GLuint AttribLocation, GLuint numComponents, GLenum type, GLsizei stride, void* offset);

	// Collega (bind) il VAO, rendendolo attivo
	void Bind();

	// Scollega (unbind) il VAO, rendendolo inattivo
	void Unbind();

private:

	GLuint ID; // Identificatore OpenGL del VAO
};

