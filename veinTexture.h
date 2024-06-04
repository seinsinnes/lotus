#include <random>
#include "Texture.h"

typedef struct Particle {
	int life; /*Whether the particle is active and how big it is*/
	int attraction_rate;	
	int y_pos; 
	int x_pos;
	float colour[4];
} Particle;


class veinTexture: public Texture {
	public:
		veinTexture(int x_seg, int y_seg, int particle_num = 18, float vein_colour_red = 0.95f , float vein_colour_green = 0.55f, float vein_colour_blue = 0.8f,float vein_colour_alpha = 1.0f);

	protected:
		virtual void makeTexture();
	
	private:

		int n_particles;
		float vein_colour[4];

		std::random_device rd{};
    	std::mt19937 gen{rd()};
		std::normal_distribution<float> d{0.0, 2.0};

		Particle *particles; /* This array will contain the data on
		 			the drawing particles - current position and direction and aliveness */

		void init_particles();
		int find_nearest(int particle_indx);
		void moveTowardNearest(int particle_indx);
		void drawParticle(int particle_indx, int y_size);
};



