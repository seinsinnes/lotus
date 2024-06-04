// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#if defined(__APPLE__)
#include <GL/glew.h>
#else
#include <GL/glew.h>
#endif
// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "shader.hpp"
#include "lotusObject.h"

int fillVertexBuffer(lotusObject *lot, GLfloat *vertex_buffer, GLfloat *colour_buffer)
{
	mesh pet;
	int faces_copied = 0;
	for(int j = 1;j<lot->petal_count;j++)
	{
		pet = lot->lotus[j];
		for(int i = 0;i< pet.face_count;i++)
		{
			vertex_buffer[faces_copied*3*6 + 0] = pet.vertices[pet.faces[i][0]][0];
			vertex_buffer[faces_copied*3*6 + 1] = pet.vertices[pet.faces[i][0]][1];
			vertex_buffer[faces_copied*3*6 + 2] = pet.vertices[pet.faces[i][0]][2];

			vertex_buffer[faces_copied*3*6 + 3] = pet.vertices[pet.faces[i][1]][0];
			vertex_buffer[faces_copied*3*6 + 4] = pet.vertices[pet.faces[i][1]][1];
			vertex_buffer[faces_copied*3*6 + 5] = pet.vertices[pet.faces[i][1]][2];

			vertex_buffer[faces_copied*3*6 + 6] = pet.vertices[pet.faces[i][2]][0];
			vertex_buffer[faces_copied*3*6 + 7] = pet.vertices[pet.faces[i][2]][1];
			vertex_buffer[faces_copied*3*6 + 8] = pet.vertices[pet.faces[i][2]][2];

			vertex_buffer[faces_copied*3*6 + 9] = pet.vertices[pet.faces[i][2]][0];
			vertex_buffer[faces_copied*3*6 + 10] = pet.vertices[pet.faces[i][2]][1];
			vertex_buffer[faces_copied*3*6 + 11] = pet.vertices[pet.faces[i][2]][2];

			vertex_buffer[faces_copied*3*6 + 12] = pet.vertices[pet.faces[i][3]][0];
			vertex_buffer[faces_copied*3*6 + 13] = pet.vertices[pet.faces[i][3]][1];
			vertex_buffer[faces_copied*3*6 + 14] = pet.vertices[pet.faces[i][3]][2];

			vertex_buffer[faces_copied*3*6 + 15] = pet.vertices[pet.faces[i][0]][0];
			vertex_buffer[faces_copied*3*6 + 16] = pet.vertices[pet.faces[i][0]][1];
			vertex_buffer[faces_copied*3*6 + 17] = pet.vertices[pet.faces[i][0]][2];

			colour_buffer[faces_copied*3*6 + 0] = 0.0002f*(i*3*6 + 0);
			colour_buffer[faces_copied*3*6 + 1] = 0.0002f*(i*3*6 + 1);
			colour_buffer[faces_copied*3*6 + 2] = 0.0002f*(i*3*6 + 2);
			
			colour_buffer[faces_copied*3*6 + 3] = 0.0002f*(i*3*6 + 3);
			colour_buffer[faces_copied*3*6 + 4] = 0.0002f*(i*3*6 + 4);
			colour_buffer[faces_copied*3*6 + 5] = 0.0002f*(i*3*6 + 5);
			
			colour_buffer[faces_copied*3*6 + 6] = 0.0002f*(i*3*6 + 6);
			colour_buffer[faces_copied*3*6 + 7] = 0.0002f*(i*3*6 + 7);
			colour_buffer[faces_copied*3*6 + 8] = 0.0002f*(i*3*6 + 8);

			colour_buffer[faces_copied*3*6 + 9] = 0.0002f*(i*3*6 + 9);
			colour_buffer[faces_copied*3*6 + 10] = 0.0002f*(i*3*6 + 10);
			colour_buffer[faces_copied*3*6 + 11] = 0.0002f*(i*3*6 + 11);

			colour_buffer[faces_copied*3*6 + 12] = 0.0002f*(i*3*6 + 12);
			colour_buffer[faces_copied*3*6 + 13] = 0.0002f*(i*3*6 + 13);
			colour_buffer[faces_copied*3*6 + 14] = 0.0002f*(i*3*6 + 14);

			colour_buffer[faces_copied*3*6 + 15] = 0.0002f*(i*3*6 + 15);
			colour_buffer[faces_copied*3*6 + 16] = 0.0002f*(i*3*6 + 16);
			colour_buffer[faces_copied*3*6 + 17] = 0.0002f*(i*3*6 + 17);
			faces_copied++;
		}
	}
}

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Lotus", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(0,3,-15), // Camera is at (4,3,-3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	int x_segments=16;
	int y_segments=14;
	lotusObject *lot = new lotusObject(6,3, x_segments, y_segments);

	int total_face_count = 0;
	for(int i = 0;i<lot->petal_count;i++)
	{
		total_face_count += lot->lotus[i].face_count;
	}

	GLfloat *g_vertex_buffer_data = new GLfloat[total_face_count*6*3];
	GLfloat *g_colour_buffer_data = new GLfloat[total_face_count*6*3];

	fillVertexBuffer(lot, g_vertex_buffer_data, g_colour_buffer_data);


	for(int i = 0;i< total_face_count*6;i++)
	{
		std::cout << "v " << g_vertex_buffer_data[i*3 + 0 ] << ", " << g_vertex_buffer_data[i*3 + 1 ] << ", " << g_vertex_buffer_data[i*3 + 2] << std::endl;
	}

	for(int i = 0;i< total_face_count*2;i++)
	{
		std::cout << "f " << i*3 + 1 << ", " << i*3 + 2 << ", " << i*3 + 3 << std::endl;
	}
	// One colour for each vertex. They were generated randomly.
	/*static const GLfloat g_colour_buffer_data[] = { 
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
		0.982f,  0.099f,  0.879f
	};*/

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*total_face_count*6*3, g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint colourbuffer;
	glGenBuffers(1, &colourbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*total_face_count*6*3, g_colour_buffer_data, GL_STATIC_DRAW);

	float rotation_speed = 0;

	do{

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);
		if(glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS)
		{
			MVP = glm::rotate(MVP, glm::radians(-1.0f), glm::vec3(1,0,0));
		}
		if(glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS)
		{
			MVP = glm::rotate(MVP, glm::radians(1.0f), glm::vec3(1,0,0));
		}

		MVP = glm::rotate(MVP, glm::radians(rotation_speed), glm::vec3(0,0,1));

		if(glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS)
		{
			rotation_speed-=0.01;
		}
		if(glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS)
		{
			rotation_speed+=0.01;
		}
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, total_face_count*6); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colourbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

