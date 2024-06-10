#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include "Texture.h"


GLuint Texture::createGLTexture(GLuint texID) {


	makeTexture();


	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);   	
	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, SEGMENT_DETAIL, SEGMENT_DETAIL, 0, GL_RGBA, GL_FLOAT, &image);
	
	return texID;
}

void Texture::makeTexture() {

}

Texture::Texture() {
}

