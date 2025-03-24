#include "lxwindows.h"

#ifdef LXW_USE_X11
#include "x11_window.h"

void lxw_set_window_size(lxwindow window, int w, int h) {
	x11_window* xwindow = (x11_window*)window;
	XResizeWindow(xwindow->display, xwindow->window, w, h);
	XFlush(xwindow->display);
}

void lxw_set_window_pos(lxwindow window, int x, int y) {
	x11_window* xwindow = (x11_window*)window;
	XMoveWindow(xwindow->display, xwindow->window, x, y);
	XFlush(xwindow->display);
}

void lxw_set_window_name(lxwindow window, char* name) {
	x11_window* xwindow = (x11_window*)window;
	XStoreName(xwindow->display, xwindow->window, name);
	XFlush(xwindow->display);
}

#endif
