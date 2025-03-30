#include "lxwindows.h"

#ifdef LXW_USE_X11
#include "x11_window.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int lxw_init() {
	return 1;
}

lxwindow lxw_create_window(int width, int height, const char* name) {
	x11_window* window = (x11_window*)malloc(sizeof(x11_window));

	window->display = XOpenDisplay(NULL);
	assert(window->display != NULL);

	int screen = DefaultScreen(window->display);
	Window root = RootWindow(window->display, screen);

	int glx_attr[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	window->vi = glXChooseVisual(window->display, screen, glx_attr);
	assert(window->vi != NULL);

	XSetWindowAttributes swa;
	swa.colormap = XCreateColormap(window->display, root, window->vi->visual, AllocNone);
	swa.event_mask = ExposureMask | KeyPressMask;

	window->window = XCreateWindow(
			window->display,
			root,
			0,
			0,
			width,
			height,
			0,
			window->vi->depth,
			InputOutput,
			window->vi->visual,
			CWColormap | CWEventMask,
			&swa);

	XStoreName(window->display, window->window, name);

	window->delete_message = XInternAtom(window->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(window->display, window->window, &window->delete_message, 1);

	XMapWindow(window->display, window->window);
	XSelectInput(window->display, window->window, StructureNotifyMask);

	window->width = width;
	window->height = height;
	window->running = 1;

	_lxw_add_window(window, (char*)name);
	return (lxwindow)window;
}

void lxw_process_window(lxwindow window) {
	x11_window* xwindow = (x11_window*)window;
	XEvent event;

	while (XPending(xwindow->display)) {
		XNextEvent(xwindow->display, &event);

		switch (event.type) {
			case ClientMessage:
				if ((Atom)event.xclient.data.l[0] == xwindow->delete_message) {
					xwindow->running = 0;
				}
				break;

			case ConfigureNotify:
				if (event.xconfigure.width != xwindow->width || event.xconfigure.height != xwindow->height) {
					xwindow->width = event.xconfigure.width;
					xwindow->height = event.xconfigure.height;
					glViewport(0, 0, xwindow->width, xwindow->height);
				}
				break;

			default:
				break;
		}
	}
}

int lxw_window_is_open(lxwindow window) {
	x11_window* xwindow = (x11_window*)window;
	return xwindow->running;
}

void lxw_destroy_window(lxwindow window) {
	x11_window* xwindow = (x11_window*)window;

	if (xwindow->has_context) {
		glXMakeCurrent(xwindow->display, None, NULL);
		glXDestroyContext(xwindow->display, xwindow->context);
	}
	
	XDestroyWindow(xwindow->display, xwindow->window);
	XCloseDisplay(xwindow->display);
	free(xwindow);
}

void lxw_make_gl_context(lxwindow window) {
	x11_window* xwindow = (x11_window*)window;

	xwindow->context = glXCreateContext(xwindow->display, xwindow->vi, NULL, GL_TRUE);
	glXMakeCurrent(xwindow->display, xwindow->window, xwindow->context);

	xwindow->has_context = 1;
}

void lxw_swap_buffers(lxwindow window) {
	x11_window* xwindow = (x11_window*)window;

	int w,h;
	lxw_query_window_size(window, &w, &h);

	if (w > 0 && h > 25) {
		glXSwapBuffers(xwindow->display, xwindow->window);
	}
}

#endif
