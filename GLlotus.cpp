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

int fillVertexBuffer(lotusObject *lot, GLfloat *vertex_buffer, GLfloat *colour_buffer, GLfloat *texcoord_buffer)
{
	mesh pet;
	int faces_copied = 0;
	for(int j = 1;j<lot->petal_count;j++)
	{
		pet = lot->lotus[j];
		for(int x = 0;x<lot->m_x_segments;x++) {
		for(int y = 0;y<(lot->m_y_segments);y++)
		{
			int i = x*lot->m_y_segments + y;
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

			colour_buffer[faces_copied*3*6 + 0] = 0.0002f*((i)*3*6 + 0);
			colour_buffer[faces_copied*3*6 + 1] = 0.0002f*((i)*3*6 + 1);
			colour_buffer[faces_copied*3*6 + 2] = 0.0002f*((i)*3*6 + 2);
			
			colour_buffer[faces_copied*3*6 + 3] = 0.0002f*((i)*3*6 + 3);
			colour_buffer[faces_copied*3*6 + 4] = 0.0002f*((i)*3*6 + 4);
			colour_buffer[faces_copied*3*6 + 5] = 0.0002f*((i)*3*6 + 5);
			
			colour_buffer[faces_copied*3*6 + 6] = 0.0002f*((i)*3*6 + 6);
			colour_buffer[faces_copied*3*6 + 7] = 0.0002f*((i)*3*6 + 7);
			colour_buffer[faces_copied*3*6 + 8] = 0.0002f*((i)*3*6 + 8);

			colour_buffer[faces_copied*3*6 + 9] = 0.0002f*((i)*3*6 + 9);
			colour_buffer[faces_copied*3*6 + 10] = 0.0002f*((i)*3*6 + 10);
			colour_buffer[faces_copied*3*6 + 11] = 0.0002f*((i)*3*6 + 11);

			colour_buffer[faces_copied*3*6 + 12] = 0.0002f*((i)*3*6 + 12);
			colour_buffer[faces_copied*3*6 + 13] = 0.0002f*((i)*3*6 + 13);
			colour_buffer[faces_copied*3*6 + 14] = 0.0002f*((i)*3*6 + 14);

			colour_buffer[faces_copied*3*6 + 15] = 0.0002f*((i)*3*6 + 15);
			colour_buffer[faces_copied*3*6 + 16] = 0.0002f*((i)*3*6 + 16);
			colour_buffer[faces_copied*3*6 + 17] = 0.0002f*((i)*3*6 + 17);


			texcoord_buffer[faces_copied*2*6 + 0] = (1.0f/(lot->m_y_segments + 1))*y;
			texcoord_buffer[faces_copied*2*6 + 1] = (1.0f/(lot->m_x_segments + 1))*x;
			
			texcoord_buffer[faces_copied*2*6 + 2] = (1.0f/(lot->m_y_segments + 1))*(y + 1);
			texcoord_buffer[faces_copied*2*6 + 3] = (1.0f/(lot->m_x_segments + 1))*x;
			
			texcoord_buffer[faces_copied*2*6 + 4] = (1.0f/(lot->m_y_segments + 1))*(y + 1);
			texcoord_buffer[faces_copied*2*6 + 5] = (1.0f/(lot->m_x_segments + 1))*(x + 1);

			texcoord_buffer[faces_copied*2*6 + 6] = (1.0f/(lot->m_y_segments + 1))*(y + 1);
			texcoord_buffer[faces_copied*2*6 + 7] = (1.0f/(lot->m_x_segments + 1))*(x + 1);

			texcoord_buffer[faces_copied*2*6 + 8] = (1.0f/(lot->m_y_segments + 1))*y;
			texcoord_buffer[faces_copied*2*6 + 9] = (1.0f/(lot->m_x_segments + 1))*(x + 1);

			texcoord_buffer[faces_copied*2*6 + 10] = (1.0f/(lot->m_y_segments + 1))*y;
			texcoord_buffer[faces_copied*2*6 + 11] = (1.0f/(lot->m_x_segments + 1))*x;



			faces_copied++;
		}
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
	//glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glClearColor(0.122f, 0.188f, 0.369f, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

	glUseProgram(programID);

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	glUniform1i(glGetUniformLocation(programID, "tex1"), 0);
	glUniform1i(glGetUniformLocation(programID, "tex2"), 1);


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
	for(int i = 1;i<lot->petal_count;i++)
	{
		total_face_count += lot->lotus[i].face_count;
	}

	GLfloat *g_vertex_buffer_data = new GLfloat[total_face_count*6*3];
	GLfloat *g_colour_buffer_data = new GLfloat[total_face_count*6*3];
	GLfloat *g_texcoord_buffer_data = new GLfloat[total_face_count*6*2];

	fillVertexBuffer(lot, g_vertex_buffer_data, g_colour_buffer_data, g_texcoord_buffer_data);

	/*for(int i = 0;i< total_face_count*6;i++)
	{
		std::cout << "v " << g_texcoord_buffer_data[i*2 + 0 ] << ", " << g_texcoord_buffer_data[i*2 + 1 ] << std::endl;
	}
	*/

	/*for(int i = 0;i< total_face_count*6;i++)
	{
		std::cout << "v " << g_vertex_buffer_data[i*3 + 0 ] << ", " << g_vertex_buffer_data[i*3 + 1 ] << ", " << g_vertex_buffer_data[i*3 + 2] << std::endl;
	}

	for(int i = 0;i< total_face_count*2;i++)
	{
		std::cout << "f " << i*3 + 1 << ", " << i*3 + 2 << ", " << i*3 + 3 << std::endl;
	}*/

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*total_face_count*6*3, g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint colourbuffer;
	glGenBuffers(1, &colourbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*total_face_count*6*3, g_colour_buffer_data, GL_STATIC_DRAW);

	GLuint texcoordbuffer;
	glGenBuffers(1, &texcoordbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texcoordbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*total_face_count*6*2, g_texcoord_buffer_data, GL_STATIC_DRAW);

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

		// 3rd attribute buffer : texture Coords
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, texcoordbuffer);
		glVertexAttribPointer(
			2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, total_face_count*6); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colourbuffer);
	glDeleteBuffers(1, &texcoordbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

