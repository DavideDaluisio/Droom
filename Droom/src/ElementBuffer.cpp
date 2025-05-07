#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(std::vector<GLuint>& indices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// Il secondo parametro della funzione glBufferData() rappresenta la dimensione in byte dell'EBO
	// Il terzo parametro della funzione glBufferData() è un puntatore ai dati da caricare nell'EBO

	glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &ID);
}

void ElementBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void ElementBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}