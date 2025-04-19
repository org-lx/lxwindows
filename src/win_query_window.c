#include "lxwindows.h"

#ifdef LXW_USE_WINDOWS
#include "win_window.h"

#include <stdlib.h>

void lxw_query_window_size(lxwindow window, int* w, int* h) {
	win_window* wwindow = (win_window*)window;

	RECT rect;
	GetWindowRect(wwindow->hwnd, &rect);
	*w = rect.right - rect.left;
	*h = rect.bottom - rect.top;
}

void lxw_query_window_pos(lxwindow window, int* x, int* y) {
	win_window* wwindow = (win_window*)window;

	RECT rect;
	GetWindowRect(wwindow->hwnd, &rect);
	*x = rect.left;
	*y = rect.top;
}

const char* lxw_query_window_name(lxwindow window) {
	win_window* wwindow = (win_window*)window;
	static char title[256]; 
	GetWindowText(wwindow->hwnd, (LPWSTR)title, 255);
	return title;
}

#endif
