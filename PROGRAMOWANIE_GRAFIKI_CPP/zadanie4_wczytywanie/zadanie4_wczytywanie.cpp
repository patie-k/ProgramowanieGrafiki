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


bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
	){
		printf("Loading OBJ file %s...\n", path);

		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		std::vector<glm::vec3> temp_vertices; 
		std::vector<glm::vec2> temp_uvs;
		std::vector<glm::vec3> temp_normals;


		FILE * file = fopen(path, "r");
		if( file == NULL ){
			printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
			getchar();
			return false;
		}

		while( 1 ){

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

			// else : parse lineHeader

			if ( strcmp( lineHeader, "v" ) == 0 ){
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
				temp_vertices.push_back(vertex);
			}else if ( strcmp( lineHeader, "vt" ) == 0 ){
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y );
				uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
				temp_uvs.push_back(uv);
			}else if ( strcmp( lineHeader, "vn" ) == 0 ){
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
				temp_normals.push_back(normal);
			}else if ( strcmp( lineHeader, "f" ) == 0 ){
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
				if (matches != 9){
					printf("File can't be read by our simple parser :-( Try exporting with other options\n");
					return false;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices    .push_back(uvIndex[0]);
				uvIndices    .push_back(uvIndex[1]);
				uvIndices    .push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}else{
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}

		}

		// For each vertex of each triangle
		for( unsigned int i=0; i<vertexIndices.size(); i++ ){

			// Get the indices of its attributes
			unsigned int vertexIndex = vertexIndices[i];
			unsigned int uvIndex = uvIndices[i];
			unsigned int normalIndex = normalIndices[i];

			// Get the attributes thanks to the index
			glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
			glm::vec2 uv = temp_uvs[ uvIndex-1 ];
			glm::vec3 normal = temp_normals[ normalIndex-1 ];

			// Put the attributes in buffers
			out_vertices.push_back(vertex);
			out_uvs     .push_back(uv);
			out_normals .push_back(normal);

		}

		return true;
}


GLuint loadBMP(const char * imagepath){

	printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file) {
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); 
		getchar(); 
		return 0;
	}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if ( fread(header, 1, 54, file)!=54 ) { 
		printf("Not a correct BMP file\n");
		return 0;
	}
	// A BMP files always begins with "BM"
	if ( header[0]!='B' || header[1]!='M' ) {
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Make sure this is a 24bpp file
	if ( *(int*)&(header[0x1E])!=0  ) {
		printf("Not a correct BMP file\n");    
		return 0;
	}
	if ( *(int*)&(header[0x1C])!=24 ) {
		printf("Not a correct BMP file\n");    
		return 0;
	}

	// Read the information about the image
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);

	// Everything is in memory now, the file wan be closed
	fclose (file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// OpenGL has now copied the data. Free our own version
	delete [] data;

	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return textureID;
}



int OpenWindow() {
	// Otwiera okno i tworzy kontekst OpenGL 
	window = glfwCreateWindow( 800, 600, "Zadanie 4", NULL, NULL);
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

	//GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);

	// Tworzy i kompiluje nasz program GLSL z shaderow
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	GLuint Texture = loadBMP("texture.bmp");
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("cube.obj", vertices, uvs, normals);
	
	static const GLfloat cubeVertices[] = { 
		-1.0f,-1.0f,-1.0f, 
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 

         1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,

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

	static const GLfloat g_uv_buffer_data[] = {
		0.000059f, 1.0f-0.000004f,
		0.000103f, 1.0f-0.336048f,
		0.335973f, 1.0f-0.335903f,
		1.000023f, 1.0f-0.000013f,
		0.667979f, 1.0f-0.335851f,
		0.999958f, 1.0f-0.336064f,
		0.667979f, 1.0f-0.335851f,
		0.336024f, 1.0f-0.671877f,
		0.667969f, 1.0f-0.671889f,
		1.000023f, 1.0f-0.000013f,
		0.668104f, 1.0f-0.000013f,
		0.667979f, 1.0f-0.335851f,
		0.000059f, 1.0f-0.000004f,
		0.335973f, 1.0f-0.335903f,
		0.336098f, 1.0f-0.000071f,
		0.667979f, 1.0f-0.335851f,
		0.335973f, 1.0f-0.335903f,
		0.336024f, 1.0f-0.671877f,
		1.000004f, 1.0f-0.671847f,
		0.999958f, 1.0f-0.336064f,
		0.667979f, 1.0f-0.335851f,
		0.668104f, 1.0f-0.000013f,
		0.335973f, 1.0f-0.335903f,
		0.667979f, 1.0f-0.335851f,
		0.335973f, 1.0f-0.335903f,
		0.668104f, 1.0f-0.000013f,
		0.336098f, 1.0f-0.000071f,
		0.000103f, 1.0f-0.336048f,
		0.000004f, 1.0f-0.671870f,
		0.336024f, 1.0f-0.671877f,
		0.000103f, 1.0f-0.336048f,
		0.336024f, 1.0f-0.671877f,
		0.335973f, 1.0f-0.335903f,
		0.667969f, 1.0f-0.671889f,
		1.000004f, 1.0f-0.671847f,
		0.667979f, 1.0f-0.335851f
	};

	// Funkcje sprawdzania glebokosci na planie
	glEnable(GL_DEPTH_TEST);

	// Wyswietl fragment jezeli jest blizej kamery
	glDepthFunc(GL_LESS);

	GLuint vertexbuffer[2];
	glGenBuffers(2, vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	mat4 projection, view, model, cube1MVP, cube2MVP;

	model = mat4(1.0f);

	glm::vec3 position = glm::vec3( 0, 2, 10 );

	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float initialFoV = 45.0f;
	float speed = 0.001f;
	float mouseSpeed = 0.0005f;

	double xpos, ypos;

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	GLuint texturebuffer;
	glGenBuffers(1, &texturebuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texturebuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(TextureID, 0);

		static double lastTime = glfwGetTime();
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
		}

		projection = perspective(initialFoV, 4.0f / 3.0f, 0.1f, 100.0f);
		view = glm::lookAt(position, position+direction, up);

		cube1MVP = projection*view*Translate(-2, 0, 0)*model;
		
		cube2MVP = projection*view*Translate(2, 0, 0)*model;

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
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

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &cube1MVP[0][0]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
		glVertexAttribPointer(
			0,                  
			3,                 
			GL_FLOAT,           
			GL_FALSE,           
			0,                  
			(void*)0           
			);
		glDrawArrays(GL_TRIANGLES, 0, 12*3);

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &cube2MVP[0][0]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);
		glVertexAttribPointer(
			0,                  
			3,                 
			GL_FLOAT,           
			GL_FALSE,           
			0,                  
			(void*)0           
			);
		glDrawArrays(GL_TRIANGLES, 0, 12*3);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteBuffers(2, vertexbuffer);
	//glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}