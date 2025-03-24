#include "lxwindows.h"

#ifdef LXW_USE_X11
#include "x11_window.h"

void lxw_query_window_size(lxwindow window, int* w, int* h) {
	x11_window* xwindow = (x11_window*)window;
	XWindowAttributes attrs;
	XGetWindowAttributes(xwindow->display, xwindow->window, &attrs);

	*w = attrs.width;
	*h = attrs.height;
}

void lxw_query_window_pos(lxwindow window, int* x, int* y) {
	x11_window* xwindow = (x11_window*)window;
	XWindowAttributes attrs;
	XGetWindowAttributes(xwindow->display, xwindow->window, &attrs);

	*x = attrs.x;
	*y = attrs.y;
}

char* lxw_query_window_name(lxwindow window) {
	char* window_name;
	x11_window* xwindow = (x11_window*)window;
	XFetchName(xwindow->display, xwindow->window, &window_name);
	return window_name;
}

#endif
