#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

/*
 * Compiles a shader and returns the handle
 * typeName is the type of shader to print in errors, i.e. "vertex" or "fragment"
 */
GLint compile_shader(const GLchar* source, const GLenum type, const GLchar* typeName);

/*
 * Small class to create a shader
 */

class Shader {
public:
	// Program ID
	GLuint program;
	// Constructor
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);
	// Use the program
	void use();
};

#endif SHADER_H
