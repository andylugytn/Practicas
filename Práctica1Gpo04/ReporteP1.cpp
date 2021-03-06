#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Reporte Practica 1", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);

	//Verificación de errores de creacion  ventana
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		//x,y,z A
		-0.7f,  -0.4f, 0.0f,   1.0f,0.0f,0.0f,   // A-0
		-0.5f,  0.6f, 0.0f,   1.0f,0.0f,1.0f,   // B-1
		-0.3f,  -0.4f, 0.0f,   1.0f,1.0f,0.0f,   // C-2

		-0.6f,  0.1f, 0.0f,   1.0f,1.0f,0.0f,   // D-3
		-0.4f,  0.1f, 0.0f,   1.0f,1.0f,0.0f,   // E-4
		//x,y,z C
		0.2f,  0.6f, 0.0f,   1.0f,0.0f,1.0f,   // F-5
		-0.2f,  0.6f, 0.0f,   1.0f,0.0f,0.0f,   // G-6
		-0.2f,  -0.4f, 0.0f,   1.0f,1.0f,0.0f,   // H-7
		0.2f,  -0.4f, 0.0f,   1.0f,1.0f,0.0f,   // I-8
		//x,y,z G
		0.7f,  0.6f, 0.0f,   1.0f,1.0f,0.0f,   // J-9
		 0.3f,  0.6f, 0.0f,   1.0f,0.0f,0.0f,   // K-10
		 0.3f,  -0.4f, 0.0f,   1.0f,1.0f,0.0f,   // L-11
		 0.7f,  -0.4f, 0.0f,   1.0f,0.0f,1.0f,   // M-12
		0.7f,  0.0f, 0.0f,   1.0f,1.0f,0.0f,   // N-13
		0.5f,  0.0f, 0.0f,   1.0f,1.0f,0.0f,   // O-14
		

	};
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,

	};



	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)



	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glBindVertexArray(VAO);
		glPointSize(10);
		//TRIANGLES, POINTS, LINES
		//GLDRAWELEMENTS TRABAJA CON EBO
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); //PRIMER TRIÁNGULO 1-4
		//glDrawElements(GL_POINTS, 3, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT,0);
		//glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(3 * sizeof(GLfloat)));//CORRIMIENTO DE MEMORIA PARA 2DO TRIANGULO 0-3

		//GLDRAWARRAYS TRABAJA DIRECTO CON INDICES
		//DIBUJANDO TRAPECIO RELLENO
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawArrays(GL_TRIANGLES, 1, 3);
		//glDrawArrays(GL_TRIANGLES, 2, 3);
		//DIBUJANDO PENTAGONO RELLENO
		//glDrawArrays(GL_TRIANGLES, 5, 3);
		//glDrawArrays(GL_TRIANGLES, 6, 3);
		//glDrawArrays(GL_TRIANGLES, 7, 3);

		//DIBUJANDO A
		glDrawArrays(GL_LINE_STRIP, 0, 3);
		glDrawArrays(GL_LINE_STRIP, 3, 2);
		//DIBUJANDO C
		glDrawArrays(GL_LINE_STRIP, 5, 4);
		//DIBUJANDO G
		glDrawArrays(GL_LINE_STRIP, 9, 6);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}