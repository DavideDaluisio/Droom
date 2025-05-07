#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

void VertexArray::LinkAttrib(VertexBuffer& VertexBuffer, GLuint AttribLocation, GLuint numComponents, GLenum type, GLsizei stride, void* offset)
{
	VertexBuffer.Bind();

	// Specifica come OpenGL deve interpretare i dati dell'attributo di vertice:
	// - AttribLocation: indice dell'attributo nel layout dello shader
	// - numComponents: numero di componenti per vertice (es. 3 per vec3)
	// - type: tipo dei dati (es. GL_FLOAT)
	// - GL_FALSE: indica che i dati non devono essere normalizzati
	// - stride: numero di byte tra un attributo e il successivo
	// - offset: posizione iniziale dell'attributo nei dati del VBO
	glVertexAttribPointer(AttribLocation, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(AttribLocation);
	VertexBuffer.Unbind();
}

void VertexArray::Bind()
{
	glBindVertexArray(ID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}