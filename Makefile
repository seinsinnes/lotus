CC = g++ -Wall

all:
	$(CC) -std=c++20 -I/opt/homebrew/include/ -L/opt/homebrew/lib -lglfw -lglew -framework OpenGL GLlotus.cpp veinTexture.cpp lotusObject.cpp gradientTexture.cpp Texture.cpp shader.cpp -o GLlotus 
