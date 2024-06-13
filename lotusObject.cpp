/*lotusObject.c draws a 3D lotus using opengl - Written by Chris Day 2008*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <iostream>

#include "veinTexture.h"
#include "gradientTexture.h"

#include "lotusObject.h"



GLvoid lotusObject :: CalculateVectorNormal(int indx_lotus, int indx_face) {
    GLfloat Qx, Qy, Qz, Px, Py, Pz;
	GLfloat fVert1[3], fVert2[3], fVert3[3];

	fVert1[0] = lotus[indx_lotus].vertices[lotus[indx_lotus].faces[indx_face][0]][0];
	fVert1[1] = lotus[indx_lotus].vertices[lotus[indx_lotus].faces[indx_face][0]][1];
	fVert1[2] = lotus[indx_lotus].vertices[lotus[indx_lotus].faces[indx_face][0]][2];

	fVert2[0] = lotus[indx_lotus].vertices[lotus[indx_lotus].faces[indx_face][1]][0];
	fVert2[1] = lotus[indx_lotus].vertices[lotus[indx_lotus].faces[indx_face][1]][1];
	fVert2[2] = lotus[indx_lotus].vertices[lotus[indx_lotus].faces[indx_face][1]][2];

	fVert3[0] = lotus[indx_lotus].vertices[lotus[indx_lotus].faces[indx_face][2]][0];
	fVert3[1] = lotus[indx_lotus].vertices[lotus[indx_lotus].faces[indx_face][2]][1];
	fVert3[2] = lotus[indx_lotus].vertices[lotus[indx_lotus].faces[indx_face][2]][2];

	Qx = fVert2[0]-fVert1[0];
	Qy = fVert2[1]-fVert1[1];
	Qz = fVert2[2]-fVert1[2];
	Px = fVert3[0]-fVert1[0];
	Py = fVert3[1]-fVert1[1];
	Pz = fVert3[2]-fVert1[2];

	lotus[indx_lotus].normals[indx_face][0]= Py*Qz - Pz*Qy;
	lotus[indx_lotus].normals[indx_face][1] = Pz*Qx - Px*Qz;
	lotus[indx_lotus].normals[indx_face][2] = Px*Qy - Py*Qx;

}

void lotusObject :: meshDuplicate(int indx_old, int indx_new) {
	int i;
	for(i=0;i<lotus[indx_old].vertex_count;i++) {

		lotus[indx_new].vertices[i][0] = lotus[indx_old].vertices[i][0];
		lotus[indx_new].vertices[i][1] = lotus[indx_old].vertices[i][1];
		lotus[indx_new].vertices[i][2] = lotus[indx_old].vertices[i][2];
	}
	lotus[indx_new].vertex_count = lotus[indx_old].vertex_count;

	for(i=0;i<lotus[indx_old].face_count;i++) {
		lotus[indx_new].faces[i][0] = lotus[indx_old].faces[i][0];
		lotus[indx_new].faces[i][1] = lotus[indx_old].faces[i][1];
		lotus[indx_new].faces[i][2] = lotus[indx_old].faces[i][2];
		lotus[indx_new].faces[i][3] = lotus[indx_old].faces[i][3];
		CalculateVectorNormal(indx_new, i);

	}
	lotus[indx_new].face_count = lotus[indx_old].face_count;
}

void lotusObject :: doZRotation(int indx, float angle) {
	float c = cos(angle);
	float s = sin(angle);
	float x_new, y_new;
	int i;
	
	for(i=0;i<lotus[indx].vertex_count;i++) {
		x_new = lotus[indx].vertices[i][0]*c - lotus[indx].vertices[i][1]*s;
		y_new = lotus[indx].vertices[i][0]*s + lotus[indx].vertices[i][1]*c;
		lotus[indx].vertices[i][0] = x_new;
		lotus[indx].vertices[i][1] = y_new;
		lotus[indx].vertices[i][2] = lotus[indx].vertices[i][2];
	}

	for(i=0;i<lotus[indx].face_count;i++) {
		CalculateVectorNormal(indx, i);
	}



}

void lotusObject :: doYRotation(int indx, float angle) {
	float c = cos(angle);
	float s = sin(angle);
	float x_new, z_new;
	int i;
	
	for(i=0;i<lotus[indx].vertex_count;i++) {
		x_new = lotus[indx].vertices[i][0]*c - lotus[indx].vertices[i][2]*s;
		z_new = lotus[indx].vertices[i][0]*s + lotus[indx].vertices[i][2]*c;
		lotus[indx].vertices[i][0] = x_new;
		lotus[indx].vertices[i][1] = lotus[indx].vertices[i][1];
		lotus[indx].vertices[i][2] = z_new;
	}

	for(i=0;i<lotus[indx].face_count;i++) {
		CalculateVectorNormal(indx, i);
	}



}



/*ellipticalConnect produces the vertices along an elliptical path between points (v1_x,v1_y,0) and
 (v2_x,v2_y,0) in 'segments' intervals.*/
void lotusObject :: ellipticalConnect(int indx, float a, float v1_x, float v1_y, float v2_x,float v2_y, int segments) {

	float step, h, k, b, j, z;
	int i;

	step = (v1_y-v2_y)/(float)segments;
	h = (v1_x + v2_x)/2.0f;
	k = (v1_y + v2_y)/2.0f;
	b = fabs(v1_y - v2_y)/2.0f;

	for(i=0;i<(segments +1);i++) {
		j = (i - ((float)segments/2.0f))*step;
		//printf( "i: %d seg: %d step: %f\n", i, segments, step);	
		z = -sqrt(fabs(pow(a,2.0f)* (pow(b,2)- pow((j-k),2)) ));	
		lotus[indx].vertices[lotus[indx].vertex_count][0] = h;
		lotus[indx].vertices[lotus[indx].vertex_count][1] = j;
		lotus[indx].vertices[lotus[indx].vertex_count][2] = z;
		//printf("x: %f y: %f z: %f\n", h, j, z);
		//printf( "%f %f %f %f\n", pow(a,2.0f), pow(b,2), pow((j-k),2), pow(a,2.0f)* (pow(b,2)- pow((j-k),2)) );
		lotus[indx].vertex_count++;
	}

}

/*createPetalVertices calculates the edge of the petal using the cubic formula: y = a + bx + cx^2 + dx^3
 and its negative. x is in the range 'start' to 'end' over 'x_seg' number of intervals. Using the edge
 defined by the cubic formulas it calls ellipticalConnect to fill in the interior vertices */
void lotusObject :: createPetalVertices(int indx, float a, float b,float c,float d, int x_seg, int y_seg, float start, float end) {
	float step, curve_pt, j;
	int i;

	float elliptical_curvature = 0.4;
	
	lotus[indx].vertex_count=0;
	step = ((end-start)/(float)x_seg);
	
	for(i=0;i<(x_seg +1);i++) {
		
		j = (float)i*(float)step + start;
		curve_pt = a + b*j + c*(pow(j,2)) + d*(pow(j,3));
		ellipticalConnect(indx, elliptical_curvature,j,curve_pt,j,-curve_pt,y_seg);
	}
	
}

/*makePetal produces the mesh data for one petal.

indx tells the function where to put the data in the array lotus
x_segments is the number of polygon segments along the length of each petal
y_segments is the number of polygon segments across the width of each petal
*/
mesh lotusObject :: makePetal(int indx, int x_seg, int y_seg) {
	int number_of_faces, j;

	float a_cubic = 1.0f;
	float b_cubic = 0.092f;
	float c_cubic = 0.15f;
	float d_cubic = -0.035f;
	float petal_edge_start = 0.0f;
	float petal_edge_end = 5.6f;

	/*First create the vertices...*/
	createPetalVertices(indx, a_cubic, b_cubic, c_cubic, d_cubic, x_seg, y_seg, petal_edge_start, petal_edge_end);
	number_of_faces = lotus[indx].vertex_count - (y_seg + 2);
	
	/*...then create the faces.*/
	lotus[indx].face_count = 0;	
	for (j = 0;j < number_of_faces; j++)
		if ((j % (y_seg + 1)) != y_seg) {
			
			lotus[indx].faces[lotus[indx].face_count][0] = j;
			lotus[indx].faces[lotus[indx].face_count][1] = j+1;
			lotus[indx].faces[lotus[indx].face_count][2] = j + y_seg + 2;
			lotus[indx].faces[lotus[indx].face_count][3] = j + y_seg + 1;
			CalculateVectorNormal(indx, lotus[indx].face_count);
			lotus[indx].face_count++;
		}

	/*for (int i=0;i<lotus[indx].vertex_count;i++)
	{
		std::cout << "v " << lotus[indx].vertices[i][0] << ", " << lotus[indx].vertices[i][1] << ", " << lotus[indx].vertices[i][2] << std::endl;
	}
	for (int i=0;i<lotus[indx].face_count;i++)
	{
		std::cout << "f " << lotus[indx].faces[i][0] +1 << ", " << lotus[indx].faces[i][1] +1 << ", " << lotus[indx].faces[i][2] +1 << ", " << lotus[indx].faces[i][3]+1 << std::endl;
	}*/
	petal_count++;
	return lotus[indx];
}

/*createLotus fills the mesh array lotus up with data for drawing a lotus bloom.
This includes vertices, faces and textures.

base_numb is the number of petals in the first layer.
petal_layers is the number of layers of petals.
x_segments is the number of polygon segments along the length of each petal
y_segments is the number of polygon segments across the width of each petal*/
void lotusObject :: createLotus(int base_numb, int petal_layers, int x_segments, int y_segments) {
	int i,j;
	int layer_decrease = 1;
	float first_layer_tilt = 0.2;

	veintex = new veinTexture(18);
	gradtex = new gradientTexture();

	/*Create one petal*/
	makePetal(0, x_segments, y_segments);

	
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texPetal[0]);
	veintex->createGLTexture(texPetal[0]);

	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &texPetal[1]);
	gradtex->createGLTexture(texPetal[1]);

	/*Copy the created petal and rotated to make flower.*/
	for(i=0;i<petal_layers;i++)
		for(j=0;j<(base_numb-(i*layer_decrease));j++){
			
			meshDuplicate(0,petal_count);
			
			doYRotation(petal_count,i*(1.5/petal_layers) + first_layer_tilt);
			doZRotation(petal_count,j*(6.28/(base_numb-i)));
			petal_count++;
		}


}

lotusObject :: lotusObject(int base_numb, int petal_layers, int x_segments, int y_segments) {
	m_x_segments = x_segments;
	m_y_segments = y_segments;

	createLotus(base_numb, petal_layers, x_segments, y_segments);
}