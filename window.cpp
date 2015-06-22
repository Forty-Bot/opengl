#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

const GLchar* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main() {\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\n\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
	"out vec4 color;\n"
	"void main() {\n"
	"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// Exit on ESC
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {
	
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	// Create a window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World!", nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glew_return = glewInit();
	if (glew_return != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(glew_return) << std::endl;
		return -1;
	}

	// Set viewport
	glViewport(0, 0, 800, 600);

	
	// Initialize the vertex shader
	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint successful;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successful);
	if (!successful) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "Error: vertex shader failed to compile:" << std::endl << infoLog << std::endl;
	}
	
	// Initialize the fragment shader
	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successful);
	if (!successful) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Error: fragment shader failed to compile:" << std::endl << infoLog << std::endl;
	}

	// Link the shader program
	GLint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(fragmentShader, GL_LINK_STATUS, &successful);
	if (!successful) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Error: shader program failed to compile:" << std::endl << infoLog << std::endl;
	}
	glUseProgram(shaderProgram);

	// Cleanup Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	// Make Two Triangles
	GLfloat vertices[][9] = {
		{	-0.5f,  0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			 0.0f,  0.0f, 0.0f,
		},
		{
			 0.0f,  0.0f, 0.0f,
		 	 0.5f,  0.5f, 0.0f,
		 	 0.5f, -0.5f, 0.0f
		}
	};

	GLuint indices[] = {
		0, 1, 2
	};

	// Stick it in a buffer
	GLuint VBO[2], VAO[2], EBO;
	glGenBuffers(2, VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(2, VAO);
	
	for (int i = 0; i < 2; i++) {
		glBindVertexArray(VAO[i]);
	
		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
		glEnableVertexAttribArray(0);

	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	// Wireframe or fill
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Main Loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	
		glUseProgram(shaderProgram);
		for (int i = 0; i < 2; i++) {
			glBindVertexArray(VAO[i]);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);
		
		glfwSwapBuffers(window);
	}
	
	//Cleanup
	glfwTerminate();
	return 0;

}
