#ifndef GRADIENTTEXTURE_HEADER_H
#define GRADIENTTEXTURE_HEADER_H

#include "Texture.h"

class gradientTexture: public Texture {

		public:
			using Texture::Texture;

		protected:
			virtual void makeTexture();
};

#endif