#pragma once

#ifdef LXW_USE_GLX
#include <GL/glx.h>
#elif LXW_USE_EGL
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct { 
	Display* display;
	Window window;
	Atom delete_message;

	// 1-6 : 0
	// 7 : has_context
	// 8 : is_running
	char details;

	int width;
	int height;
	XVisualInfo* vi;


#ifdef LXW_USE_GLX
	GLXContext context;
#elif LXW_USE_EGL
	EGLContext context;
	EGLSurface surface;
#endif
} x11_window;
