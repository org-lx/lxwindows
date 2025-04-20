#pragma once
#include "lxwindows.h"

#ifdef LXW_USE_GLX
#include <GL/glx.h>
#elif defined(LXW_USE_EGL)
#include <GL/gl.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct { 
	Display* display;
	Window window;
	Atom delete_message;
	XVisualInfo* vi;

	// 1-6 : 0
	// 7 : has_context
	// 8 : is_running
	char details;

	int width;
	int height;


#ifdef LXW_USE_GLX
	GLXContext context;
#elif defined(LXW_USE_EGL)
	EGLContext context;
	EGLSurface surface;
	EGLDisplay egl_display;
	EGLConfig config;
#endif
} x11_window;
