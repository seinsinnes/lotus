/*veinTexture.c - produces a vein-like texture - Written by Chris Day 2008*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "veinTexture.h"


void veinTexture::init_particles() {
	int i, j, x, y;

	srand ( time(NULL) );

	
	for(i=0;i<n_particles;i++) {
		particles[i].life = 1;
		particles[i].attraction_rate = 3; /* The smaller the attraction rate the faster the particles approach each other */
		particles[i].x_pos = SEGMENT_DETAIL - 1;
		particles[i].y_pos = (((SEGMENT_DETAIL)) / (n_particles -1))*(i+1) + ((rand() % 5));
		particles[i].colour[0] = vein_colour[0] ;//+ d(gen)/20.0;
		particles[i].colour[1] = vein_colour[1] ;//+ d(gen)/20.0;
		particles[i].colour[2] = vein_colour[2] ;//+ d(gen)/20.0;
		particles[i].colour[3] = vein_colour[3] ;//+ d(gen)/20.0;

	}
}

/*finds the nearest particle to particle particle_indx*/
int veinTexture::find_nearest(int particle_indx) {
	int j;
	int min_distance = SEGMENT_DETAIL;
	int min_indx = -1;
	int current_distance;
	for(j=0;j<n_particles;j++)
			if((particles[j].life > 0) && j != particle_indx) {
				current_distance = abs(particles[j].y_pos - particles[particle_indx].y_pos);
				if(current_distance < min_distance) {
					min_distance = current_distance;
					min_indx = j;
				}
			}
	return min_indx;
}

/*moves particle particle_indx toward the nearest particle */
void veinTexture::moveTowardNearest(int particle_indx) {
	int nearest = -1;
	int nearest_vec = 0;	
	
	nearest = find_nearest(particle_indx);
	nearest_vec = particles[nearest].y_pos - particles[particle_indx].y_pos;
	if(nearest_vec != 0) 					
		particles[particle_indx].y_pos += nearest_vec / abs(nearest_vec);
	else { /*If particles are on top of one another merge them */
		particles[particle_indx].life += abs(particles[nearest].life);
						
		particles[nearest].life = 0;
	}
}

void veinTexture::drawParticle(int particle_indx, int y_size) {

	int k;
	
	for(k=0;k < particles[particle_indx].life;k++){
		if((particles[particle_indx].y_pos + k) < y_size) {
			
			image[particles[particle_indx].x_pos][particles[particle_indx].y_pos + k][0] = particles[particle_indx].colour[0];
			image[particles[particle_indx].x_pos][particles[particle_indx].y_pos + k][1] = particles[particle_indx].colour[1];
			image[particles[particle_indx].x_pos][particles[particle_indx].y_pos + k][2] = particles[particle_indx].colour[2];
			image[particles[particle_indx].x_pos][particles[particle_indx].y_pos + k][3] = particles[particle_indx].colour[3];

			/*particles[particle_indx].colour[0] = particles[particle_indx].colour[0] + d(gen)/0.0;
			particles[particle_indx].colour[1] = particles[particle_indx].colour[1] + d(gen)/80.0;
			particles[particle_indx].colour[2] = particles[particle_indx].colour[2] + d(gen)/80.0;
			particles[particle_indx].colour[3] = particles[particle_indx].colour[3] + d(gen)/80.0;*/
		}
	}
}

void veinTexture::makeTexture() {
	int j;
	int y_size = SEGMENT_DETAIL;
	bool done = false;
	
	for(int x=0;x<SEGMENT_DETAIL;x++) 
		for(int y=0;y<SEGMENT_DETAIL;y++){
			image[x][y][0] = 0.0f;
			image[x][y][1] = 0.0f;
			image[x][y][2] = 0.0f;
			image[x][y][3] = 0.0f;
	}
			
	init_particles();

	while(!done)
		for(j=0;j<n_particles;j++) {
			if(particles[j].life > 0) {
				if(particles[j].x_pos > 0) {
					drawParticle(j, y_size);	
					if(particles[j].x_pos % particles[j].attraction_rate == 0)
						moveTowardNearest(j);
						
				particles[j].x_pos--;
				} else done = true;	
			}
	
		}
	
}

veinTexture::veinTexture( int particle_num, float vein_colour_red, float vein_colour_green, float vein_colour_blue,float vein_colour_alpha) : Texture() {

	n_particles = particle_num;

	vein_colour[0] = vein_colour_red;
	vein_colour[1] = vein_colour_green;
	vein_colour[2] = vein_colour_blue;
	vein_colour[3] = vein_colour_alpha;	

	particles = new Particle[n_particles];

	makeTexture();

}
