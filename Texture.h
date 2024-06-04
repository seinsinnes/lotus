#ifndef TEXTURE_HEADER_H
#define TEXTURE_HEADER_H


#define MAX_X_SEGMENTS 24
#define MAX_Y_SEGMENTS 24
#define SEGMENT_DETAIL 16 /* The resolution of each texture segment will be DETAILxDETAIL */

class Texture {
	public:
		GLuint *createGLTexture();
		Texture(int x_seg, int y_seg);
	protected:
		int x_segments;
		int y_segments;
		
		GLfloat image[MAX_X_SEGMENTS][MAX_Y_SEGMENTS][SEGMENT_DETAIL][SEGMENT_DETAIL][4]; /* This array will contain the texture data */
		virtual void makeTexture();
		
		GLuint *textures;

	
	
};
#endif