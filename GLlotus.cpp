// To compile with gcc:  (tested on Ubuntu 14.04 64bit):
//	 g++ sdl2_opengl.cpp -lSDL2 -lGL
// To compile with msvc: (tested on Windows 7 64bit)
//   cl sdl2_opengl.cpp /I C:\sdl2path\include /link C:\path\SDL2.lib C:\path\SDL2main.lib /SUBSYSTEM:CONSOLE /NODEFAULTLIB:libcmtd.lib opengl32.lib

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "lotusObject.h"

typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;

#define WinWidth 1000
#define WinHeight 1000

float xrot = 0.0f;
float zrot = 0.0f;
float zrot_speed = 0.0f;

void resizeGLScene(unsigned int width, unsigned int height){
	if (height == 0)
		height = 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
}


int initGL(){
	int x_segments=16;
	int y_segments=14;


	glEnable(GL_TEXTURE_2D);

	glClearColor(0.0, 0.0, 0.0, 0.0);	
	glClearDepth(1.0);					
	glDepthFunc(GL_LESS);				
	glEnable(GL_DEPTH_TEST);				
	glShadeModel(GL_FLAT);
	glEnable(GL_NORMALIZE);				
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	createLotus(6,3, x_segments, y_segments);

	//resizeGLScene(GLWin.width, GLWin.height);
	glFlush();
	return true;
}

int drawGLScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();					
	glTranslatef(0.0,0.0,-18.0);		

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(zrot,0.0f,0.0f,1.0f);
	zrot+=zrot_speed;	

	drawLotus();

	return true;    
}

int main (int ArgCount, char **Args)
{
  i32 winWidth, winHeight;
  u32 WindowFlags = SDL_WINDOW_OPENGL;
  SDL_Window *Window = SDL_CreateWindow("Lotus", 0, 0, WinWidth, WinHeight, WindowFlags);
  assert(Window);
  SDL_GLContext Context = SDL_GL_CreateContext(Window);

  initGL();
  SDL_GetWindowSize(Window, &winWidth, &winHeight);
  resizeGLScene(winWidth, winHeight);
  
  b32 Running = 1;
  b32 FullScreen = 0;
  while (Running)
  {
    SDL_Event Event;
    while (SDL_PollEvent(&Event))
    {
      if (Event.type == SDL_WINDOWEVENT &&
      Event.window.event == SDL_WINDOWEVENT_RESIZED)
      {
              SDL_GetWindowSize(Window, &winWidth, &winHeight);
              resizeGLScene(winWidth, winHeight);
      }
      if (Event.type == SDL_KEYDOWN)
      {
        switch (Event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            Running = 0;
            break;
          case 'f':
            FullScreen = !FullScreen;
            if (FullScreen)
            {
              SDL_SetWindowFullscreen(Window, WindowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);

            }
            else
            {
              SDL_SetWindowFullscreen(Window, WindowFlags);
              //SDL_GetWindowSize(Window, &winWidth, &winHeight);
              //resizeGLScene(winWidth, winHeight);
            }
            break;
          case SDLK_DOWN:
            xrot+=0.3f;
            break;
          case SDLK_UP:
            xrot-=0.3f;
            break;
          case SDLK_LEFT:
            zrot_speed+=0.1f;
            break;
          case SDLK_RIGHT:
            zrot_speed-=0.1f;
            break;
          default:
            break;
        }
      }
      else if (Event.type == SDL_QUIT)
      {
        Running = 0;
      }
    }

    drawGLScene();
    SDL_GL_SwapWindow(Window);
    
  }
  return 0;
}
