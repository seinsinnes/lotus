#include "Texture.h"

class gradientTexture: public Texture {

		public:
			using Texture::Texture;

		protected:
			virtual void makeTexture();
};
