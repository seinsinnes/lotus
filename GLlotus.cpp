
 
#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>

#include "veinTexture.h"
#include "lotusObject.h"

typedef struct {
    Display *dpy;
    int screen;
    Window win;
    GLXContext ctx;
    XSetWindowAttributes attr;
    int x, y;
    unsigned int width, height;
    unsigned int depth;    
} GLWindow;


static int attrListSgl[] = {GLX_RGBA, GLX_RED_SIZE, 4, 
	GLX_GREEN_SIZE, 4, 
	GLX_BLUE_SIZE, 4, 
	GLX_DEPTH_SIZE, 16,
	None
};


static int attrListDbl[] = { GLX_RGBA, GLX_DOUBLEBUFFER, 
	GLX_RED_SIZE, 4, 
	GLX_GREEN_SIZE, 4, 
	GLX_BLUE_SIZE, 4, 
	GLX_DEPTH_SIZE, 16,
	None
};


GLWindow GLWin;
Bool done;

Bool keys[256];
int key_codes[6];       /* array to hold our fetched keycodes */

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

	resizeGLScene(GLWin.width, GLWin.height);
	glFlush();
	return True;
}

int drawGLScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();					
	glTranslatef(0.0,0.0,-18.0);		

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(zrot,0.0f,0.0f,1.0f);
	zrot+=zrot_speed;	

	drawLotus();

	glXSwapBuffers(GLWin.dpy, GLWin.win);
	return True;    
}

GLvoid killGLWindow(){
	if (GLWin.ctx){
		if (!glXMakeCurrent(GLWin.dpy, None, NULL)) {
			printf("Could not release drawing context.\n");
		}
		glXDestroyContext(GLWin.dpy, GLWin.ctx);
		GLWin.ctx = NULL;
	}
  
	XCloseDisplay(GLWin.dpy);
}


Bool createGLWindow(char* title, int width, int height, int bits){
	XVisualInfo *vi;
	Colormap cmap;

	int glxMajorVersion, glxMinorVersion;
	int vidModeMajorVersion, vidModeMinorVersion;
	Atom wmDelete;
	Window winDummy;
	unsigned int borderDummy;
  
	/* get a connection */
	GLWin.dpy = XOpenDisplay(0);
	GLWin.screen = DefaultScreen(GLWin.dpy);
	XF86VidModeQueryVersion(GLWin.dpy, &vidModeMajorVersion, &vidModeMinorVersion);
		printf("XF86VidModeExtension-Version %d.%d\n", vidModeMajorVersion, vidModeMinorVersion);

	/* get an appropriate visual */
	vi = glXChooseVisual(GLWin.dpy, GLWin.screen, attrListDbl);
	if (vi == NULL)
	{
		vi = glXChooseVisual(GLWin.dpy, GLWin.screen, attrListSgl);
		printf("Only Singlebuffered Visual.\n");
	}
   
	glXQueryVersion(GLWin.dpy, &glxMajorVersion, &glxMinorVersion);
	printf("glX-Version %d.%d\n", glxMajorVersion, glxMinorVersion);
	/* create a GLX context */
	GLWin.ctx = glXCreateContext(GLWin.dpy, vi, 0, GL_TRUE);
    
	/* create a color map */
	cmap = XCreateColormap(GLWin.dpy, RootWindow(GLWin.dpy, vi->screen),
        vi->visual, AllocNone);
	GLWin.attr.colormap = cmap;
	GLWin.attr.border_pixel = 0;

   
        /* create a window*/
	GLWin.attr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | KeyReleaseMask | StructureNotifyMask;
	GLWin.win = XCreateWindow(GLWin.dpy, RootWindow(GLWin.dpy, vi->screen), 0, 0,
	 width, height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask, &GLWin.attr);
        

	wmDelete = XInternAtom(GLWin.dpy, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(GLWin.dpy, GLWin.win, &wmDelete, 1);
	XSetStandardProperties(GLWin.dpy, GLWin.win, title,
            title, None, NULL, 0, NULL);
	XMapRaised(GLWin.dpy, GLWin.win);
          
	/* connect the glx-context to the window */
	glXMakeCurrent(GLWin.dpy, GLWin.win, GLWin.ctx);
	XGetGeometry(GLWin.dpy, GLWin.win, &winDummy, &GLWin.x, &GLWin.y, &GLWin.width, &GLWin.height, &borderDummy,
	 &GLWin.depth);
	printf("Depth %d\n", GLWin.depth);
	if (glXIsDirect(GLWin.dpy, GLWin.ctx)) 
		printf("Direct Rendering enabled\n");
	else
		printf("Direct Rendering disabled\n");
	initGL();
	return True;    
}

void initKeys(){

	key_codes[0] = XKeysymToKeycode(GLWin.dpy, XK_Escape);

	key_codes[1] = XKeysymToKeycode(GLWin.dpy, XK_Down);

	key_codes[2] = XKeysymToKeycode(GLWin.dpy, XK_Up);

	key_codes[3] = XKeysymToKeycode(GLWin.dpy, XK_Right);
 
	key_codes[4] = XKeysymToKeycode(GLWin.dpy, XK_Left);

}

void keyAction(){
	if (keys[key_codes[0]])
        	done = True;  
	if(keys[key_codes[1]]) 
		xrot+=0.3f;
	if(keys[key_codes[2]]) 
		xrot-=0.3f;
	if(keys[key_codes[3]]) 
		zrot_speed+=0.1f;
	if(keys[key_codes[4]]) 
		zrot_speed-=0.1f;
}

int main(int argc, char **argv){
    XEvent event;
    
    done = False;

    createGLWindow("Lotus", 800, 600, 24);
    initKeys();


    while (!done)
    {
        /* handle the events in the queue */
        while (XPending(GLWin.dpy) > 0)
        {
            XNextEvent(GLWin.dpy, &event);
            switch (event.type)
            {
                case Expose:
	                if (event.xexpose.count != 0)
	                    break;
                    drawGLScene();
                    break;
                case ConfigureNotify:
                    if ((event.xconfigure.width != GLWin.width) || 
                        (event.xconfigure.height != GLWin.height))
                    {
                        GLWin.width = event.xconfigure.width;
                        GLWin.height = event.xconfigure.height;
                        resizeGLScene(event.xconfigure.width,
                            event.xconfigure.height);
                    }
                    break;
                case KeyPress:
                    keys[event.xkey.keycode] = True;
                    break;
                case KeyRelease:
                    keys[event.xkey.keycode] = False;
                    break;
                case ClientMessage:    
                    if (*XGetAtomName(GLWin.dpy, event.xclient.message_type) == 
                        *"WM_PROTOCOLS")
                    {
                        printf("Exiting sanely...\n");
                        done = True;
                    }
                    break;
                default:
                    break;
            }
        }
        keyAction();
        drawGLScene();
    }
    killGLWindow();
    return 0;
}
