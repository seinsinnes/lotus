CC = g++ -Wall

all:
	$(CC) -I/opt/homebrew/include/ -L/opt/homebrew/lib -lSDL2 -framework OpenGL GLlotus.cpp veinTexture.cpp lotusObject.cpp gradientTexture.cpp Texture.cpp -o GLlotus
