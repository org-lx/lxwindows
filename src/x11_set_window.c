#include "lxwindows.h"

#ifdef LXW_USE_X11
#include "x11_window.h"
#include <stdlib.h>

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

void lxw_set_window_icon(lxwindow window, unsigned char* data, int w, int h) {
	x11_window* xwindow = (x11_window*)window;
	unsigned long *icon_data = (unsigned long*)malloc((2 + w * h) * sizeof(unsigned long));
	if (!icon_data) return;

	icon_data[0] = w;
	icon_data[1] = h;

	// Convert RGBA to ARGB
	for (int i = 0; i < w * h; ++i) {
		uint8_t r = data[i * 4];
		uint8_t g = data[i * 4 + 1];
		uint8_t b = data[i * 4 + 2];
		uint8_t a = data[i * 4 + 3];

		icon_data[2 + i] = ((uint32_t)a << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
	}

	Atom net_wm_icon = XInternAtom(xwindow->display, "_NET_WM_ICON", False);
	Atom cardinal = XInternAtom(xwindow->display, "CARDINAL", False);

	XChangeProperty(
		xwindow->display,
		xwindow->window,
		net_wm_icon,
		cardinal,
		32,
		PropModeReplace,
		(unsigned char*)icon_data,
		2 + w * h
	);

	XFlush(xwindow->display);
	XSync(xwindow->display, False);

	free(icon_data);
}


void lxw_set_window_min_size(lxwindow window, int mw, int mh) {
	x11_window* xwindow = (x11_window*)window;
	XSizeHints size_hints = {
		.flags = PMinSize,
		.min_width = mw,
		.min_height = mh
	};
	
	XSetWMNormalHints(xwindow->display, xwindow->window, &size_hints);
	XFlush(xwindow->display);
}

#endif
