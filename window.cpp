#include <iostream>

// GEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

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

	//Main Loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	//Cleanup
	glfwTerminate();
	return 0;

}
