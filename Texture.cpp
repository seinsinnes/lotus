#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include "Texture.h"

GLuint *Texture::createGLTexture() {
    
	int i,j;

	makeTexture();
	
	textures = new GLuint[x_segments*y_segments];
	glGenTextures(x_segments*y_segments, &textures[0]);
  
	for(i=0;i<x_segments;i++)
		for(j=0;j<y_segments;j++) {

		glBindTexture(GL_TEXTURE_2D, textures[i*y_segments+j]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);   	
		glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, SEGMENT_DETAIL, SEGMENT_DETAIL, 0, GL_RGBA, GL_FLOAT, &image[i][j]);
	}
    
	return &textures[0];
}

void Texture::makeTexture() {

}
