CC = g++ -Wall

all:
	$(CC) GLlotus.cpp veinTexture.cpp lotusObject.cpp gradientTexture.cpp Texture.cpp -o GLlotus -L/usr/X11R6/lib -lm -lGL -lGLU -lXxf86vm -lX11

