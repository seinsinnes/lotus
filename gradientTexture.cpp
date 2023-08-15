#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include "gradientTexture.h"

void gradientTexture::makeTexture() {
	int i, j, x, y;
	for(i=0;i<x_segments;i++)
		for(j=0;j<y_segments;j++)
			for(x=0;x<SEGMENT_DETAIL;x++) 
				for(y=0;y<SEGMENT_DETAIL;y++){
					image[i][j][x][y][0] = 0.8+((i*SEGMENT_DETAIL+x)*0.002);
					image[i][j][x][y][1] = 0.5+((i*SEGMENT_DETAIL+x)*0.002);
					image[i][j][x][y][2] = 0.5+((i*SEGMENT_DETAIL+x)*0.002);
					image[i][j][x][y][3] = 1.0;
				}
}
