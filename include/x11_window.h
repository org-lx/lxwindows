#pragma once
#include <GL/glx.h>
#include <X11/Xlib.h>

typedef struct { 
	Display* display;
	Window window;
	GLXContext context;
	XVisualInfo* vi;
	Atom delete_message;

	uint8_t running;
	uint8_t has_context;

	int width;
	int height;
} x11_window;
