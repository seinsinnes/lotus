#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include "gradientTexture.h"

void gradientTexture::makeTexture() {
	int x, y;
		for(x=0;x<SEGMENT_DETAIL;x++) 
			for(y=0;y<SEGMENT_DETAIL;y++){
				image[x][y][0] = 0.8+((x)*0.001);
				image[x][y][1] = 0.5+((x)*0.001);
				image[x][y][2] = 0.5+((x)*0.001);
				image[x][y][3] = 0.97f;
			}
}
