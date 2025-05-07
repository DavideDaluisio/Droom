#pragma once
#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Shader.h"

class Texture
{
public:

	// Carica un'immagine da file, crea una texture OpenGL 2D, 
	// la configura (filtri, wrapping), la carica nella GPU (gestendo RGB/RGBA/scala di grigi),
	// genera i mipmap, e infine libera la memoria dell'immagine dalla RAM.
	Texture(const char* imageFile, const char* texType, GLuint slot);

	// Libera le risorse GPU associate alla texture
	~Texture();

	// Associa l'unità di texture a una variabile uniforme nello shader.
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	// Attiva e collega (bind) la texture, rendendola attiva
	void Bind();
	
	// Scollega (unbind) la texture, rendendola inattiva
	void Unbind();


private:

	GLuint ID; // Identificatore OpenGL del VAO

	GLuint unit; // Numero dell'unità di texture (es. 0 per GL_TEXTURE0)
};

