#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// Legge l'intero contenuto di un file e lo restituisce come stringa
std::string get_file_contents(const char* fileName);

class Shader
{
public:

	// Crea, carica e compila Vertex e Fragment Shader e li unisci in un unico ShaderProgram
	Shader(const char* vertexFile, const char* fragmentFile);
	
	// Libera le risorse GPU associate allo ShaderProgram
	~Shader();

	// Attiva il programma shader compilato, rendendolo quello attualmente usato da OpenGL
	void Activate();

	// Metodi per impostare uniform nello shader attivo con vari tipi di dati (bool, int, float, vettori, matrici).
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVec2(const std::string& name, const glm::vec2& value);
	void setVec2(const std::string& name, float x, float y);
	void setVec3(const std::string& name, const glm::vec3& value);
	void setVec3(const std::string& name, float x, float y, float z);
	void setVec4(const std::string& name, const glm::vec4& value);
	void setVec4(const std::string& name, float x, float y, float z, float w);
	void setMat2(const std::string& name, const glm::mat2& mat);
	void setMat3(const std::string& name, const glm::mat3& mat);
	void setMat4(const std::string& name, const glm::mat4& mat);

	// Restituisce l'ID dello Shader Program.
	GLuint GetID();

private:

	GLuint ID; // Identificatore OpenGL dello ShaderProgramù

	void compileErrors(unsigned int shader, const char* type);

};

