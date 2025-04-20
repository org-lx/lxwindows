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
	WCHAR title[256]; 
	static char buffer[256];
	GetWindowText(wwindow->hwnd, (WCHAR*)title, 256);
	int result = WideCharToMultiByte(CP_UTF8, 0, title, -1, buffer, sizeof(buffer), NULL, NULL);
	return title;
}

#endif
