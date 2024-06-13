#ifndef TEXTURE_HEADER_H
#define TEXTURE_HEADER_H


#define SEGMENT_DETAIL 512 /* The resolution of each texture segment will be DETAILxDETAIL */

class Texture {
	public:
		GLuint createGLTexture(GLuint texID);
		Texture();

	protected:
		GLfloat image[SEGMENT_DETAIL][SEGMENT_DETAIL][4]; /* This array will contain the texture data */
		virtual void makeTexture();

	
	
};
#endif