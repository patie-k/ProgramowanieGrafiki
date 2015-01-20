// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>

mat4 Translate(float x, float y, float z){

	//Przesuniecie o wektor

	mat4 Translation = glm::translate(
		glm::mat4(1.0f),
		glm::vec3(x, y, z));

	return Translation;

}

void Draw(GLuint buforArray[], int buforArrayIndex, int trianglesAmount){

		//Funkcja rysuje dana ilosc trojkatow(3arg) na danej tablicy punktów(1arg)
		//pod podanym indeksem(2arg)

		glBindBuffer(GL_ARRAY_BUFFER, buforArray[buforArrayIndex]);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		// Rysuj
		glDrawArrays(GL_TRIANGLES, 0, trianglesAmount*3);
}

int OpenWindow() {
	// Otwiera okno i tworzy kontekst OpenGL 
	window = glfwCreateWindow( 800, 600, "Zadanie 2", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	return 0;
}

int InitializeGLFW() {
	if( !glfwInit() ) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}
	return 0;
}

int InitializeGLEW() {
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	return 0;
}

int main( void )
{
	InitializeGLFW(); // Inicjalizacja GLFW

	OpenWindow(); // Otwiera okno i tworzy kontekst OpenGL
	 
	InitializeGLEW(); // Inicjalizacja GLEW

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Upewniamy sie, ze przechwycimy wcisniecie ESC

	glClearColor(0.f, 0.0f, 0.0f, 0.0f); // Kolor t³a

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Tworzy i kompiluje nasz program GLSL z shaderow
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");



	static const GLfloat piramidVertices[] = {
		//piramida

		//podstawa
		-1.0f, 0.0f,-1.0f,
		 0.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 1.0f,

		-1.0f, 0.0f, 1.0f,
		 0.0f, 0.0f, 0.0f,
		 1.0f, 0.0f, 1.0f,

		 1.0f, 0.0f,-1.0f,
		 0.0f, 0.0f, 0.0f,
		 1.0f, 0.0f, 1.0f,
		 
		 1.0f, 0.0f,-1.0f,
		 0.0f, 0.0f, 0.0f,
		-1.0f, 0.0f,-1.0f,

		//sciany
		-1.0f, 0.0f,-1.0f,
		 0.0f, 1.5f, 0.0f,
		-1.0f, 0.0f, 1.0f,

		-1.0f, 0.0f, 1.0f,
		 0.0f, 1.5f, 0.0f,
		 1.0f, 0.0f, 1.0f,
		 
		 1.0f, 0.0f,-1.0f,
		 0.0f, 1.5f, 0.0f,
		 1.0f, 0.0f, 1.0f,
		 
		 1.0f, 0.0f,-1.0f,
		 0.0f, 1.5f, 0.0f,
		-1.0f, 0.0f,-1.0f
	};

	static const GLfloat squareVertices[] = {
		// kwadrat

		-1.0f, 0.0f,-1.0f,
		-1.0f, 0.0f, 1.0f,
		 1.0f, 0.0f,-1.0f,

		-1.0f, 0.0f, 1.0f,
		 1.0f, 0.0f, 1.0f,
		 1.0f, 0.0f,-1.0f,
	};


	static const GLfloat cubeVertices[] = { 
		//szescian
		
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end

         1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end

         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,

         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,

        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,

         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,

        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,

         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,

         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,

         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,

         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,

         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f
	};

	static const GLfloat colorBufferData[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f
	};

	// Funkcje sprawdzania glebokosci na planie
	glEnable(GL_DEPTH_TEST);

	// Wyswietl fragment jezeli jest blizej kamery
	glDepthFunc(GL_LESS);

	GLuint vertexbuffer[3];
	glGenBuffers(3, vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(piramidVertices), piramidVertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
	
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);

	mat4 projection, view, model, pyramidMVP, cubeMVP, squareMVP;

	model = mat4(1.0f);
	/*
	glm::vec3 position = glm::vec3( 2, 1, 13 );
	
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float initialFoV = 45.0f;
	float speed = 0.001f;
	float mouseSpeed = 0.0005f;*/

	//double xpos, ypos;

	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		/*static double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);

		glfwGetCursorPos(window, &xpos, &ypos);
		glfwSetCursorPos(window, 800/2, 600/2);

		horizontalAngle += mouseSpeed * deltaTime * float( 800/2 - xpos );
		verticalAngle   += mouseSpeed * deltaTime * float( 600/2 - ypos );

		glm::vec3 direction(
		    cos(verticalAngle) * sin(horizontalAngle),
		    sin(verticalAngle),
		    cos(verticalAngle) * cos(horizontalAngle)
		);

		glm::vec3 right = glm::vec3(
		    sin(horizontalAngle - 3.14f/2.0f),
		    0,
		    cos(horizontalAngle - 3.14f/2.0f)
		);

		glm::vec3 up = glm::cross( right, direction );

		if (glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS){
		    position += direction * deltaTime * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		    position -= direction * deltaTime * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		    position += right * deltaTime * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		    position -= right * deltaTime * speed;
		} */

		projection = perspective(40.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		view = glm::lookAt(glm::vec3(-5,0,15), glm::vec3(0,0,0), glm::vec3(0,1,0));

		pyramidMVP = projection*view*Translate(-2, 0, 0)*model;
		cubeMVP = projection*view*Translate(2, 0, 0)*model;
		squareMVP = projection*view*Translate(6, -2, 0)*model;

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,					// attribute. No particular reason for 1, but must match the layout in the shader.
			3,					// size
			GL_FLOAT,			// type
			GL_FALSE,			// normalized?
			0,					// stride
			(void*)0			// array buffer offset
			);

		// Atrybut o numerze 0 - wierzcho³ki
		glEnableVertexAttribArray(0);

		//Wybranie macierzy MVP, wrzucanie do bufora i rysowanie szescianu
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &cubeMVP[0][0]);
		Draw(vertexbuffer, 0, 12);

		//Wybranie macierzy MVP, wrzucanie do bufora i rysowanie piramidy
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &pyramidMVP[0][0]);
		Draw(vertexbuffer, 1, 8);

		//Wybranie macierzy MVP, wrzucanie do bufora i rysowanie kwadratu
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &squareMVP[0][0]);
		Draw(vertexbuffer, 2, 8);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteBuffers(2, vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}