#include "shader.h"

#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

#include "util.h"

GLint compile_shader(const GLchar* source, const GLenum type, const GLchar* name) {
	
	GLint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	GLint successful;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &successful);
	if(!successful) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Error: " << name << " failed to compile:" << std::endl << infoLog << std::endl;
		// Cleanup
		glDeleteShader(shader);
		throw std::logic_error(infoLog);
	}
	return shader;

}

Shader::Shader(const GLchar* vPath, const GLchar* fPath) {

	// We don't catch any errors because if any of these parts fail then the whole shader program fails
	const GLchar* vSource = read_file(vPath).c_str();
       	const GLchar* fSource = read_file(fPath).c_str();
	GLuint vertex = compile_shader(vSource, GL_VERTEX_SHADER, vPath);
	GLuint fragment = compile_shader(fSource, GL_FRAGMENT_SHADER, fPath);

	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	GLint successful;
        GLchar infoLog[512];
	glGetProgramiv(program, GL_COMPILE_STATUS, &successful);
	if(!successful) {
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		std::cerr << "Error: program consisting of " << vPath << " and " << fPath<< " failed to link:" \
		          << std::endl << infoLog << std::endl;
		// Cleanup
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		throw std::logic_error(infoLog);
	}
	this->program = program;
	// Cleanup
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
}

void Shader::use() {

	glUseProgram(this->program);

}
