#include "lxwindows.h"

#ifdef LXW_USE_WINDOWS
#include "win_window.h"
#include "internal.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int lxw_init() {
	_lxw_window_initilize_creation_data();
	return 1;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	win_window* window = GetWindowLongPtr(hwnd, GWLP_USERDATA);

	switch (uMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
		case WM_SIZING:
			glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
			break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

lxwindow lxw_create_window(int width, int height, const char* name) {
	win_window* window = (win_window*)malloc(sizeof(win_window));

	const char* className = "lxw_window";
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = className;
	RegisterClass(&wc);

	int len = MultiByteToWideChar(CP_ACP, 0, name, -1, NULL, 0);
	wchar_t* wtitle = (wchar_t*)malloc(len * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, name, -1, wtitle, len);

	window->hwnd = CreateWindowExW(
		0, 
		className,
		wtitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		wc.hInstance,
		NULL
	);
	assert(window->hwnd != NULL);

	window->hdc = GetDC(window->hwnd);

	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 24;

	int pixelFormat = ChoosePixelFormat(window->hdc, &pfd);
	SetPixelFormat(window->hdc, pixelFormat, &pfd);

	ShowWindow(window->hwnd, SW_SHOW);
	UpdateWindow(window->hwnd);

	window->width = width;
	window->height = height;
	window->running = 1;
	
	SetWindowLongPtr(window->hwnd, GWLP_USERDATA, window);

	return (lxwindow)window;
}

void lxw_process_window(lxwindow window) {
	win_window* wwindow = (win_window*)window;
	TranslateMessage(&wwindow->msg);
	DispatchMessage(&wwindow->msg);
}

int lxw_window_is_open(lxwindow window) {
	return GetMessage(&(((win_window*)window)->msg), NULL, 0, 0);
}

void lxw_destroy_window(lxwindow window) {
	win_window* wwindow = (win_window*)window;
	if (wwindow->has_context) {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(wwindow->hglrc);
	}

	ReleaseDC(wwindow->hwnd, wwindow->hdc);
	free(wwindow);
}

void lxw_make_gl_context(lxwindow window) {
	win_window* wwindow = (win_window*)window;
	wwindow->hglrc = wglCreateContext(wwindow->hdc);
	assert(wwindow->hglrc != NULL);
	assert(wglMakeCurrent(wwindow->hdc, wwindow->hglrc) != NULL);
	wwindow->has_context = 1;
}

void lxw_swap_buffers(lxwindow window) {
	win_window* wwindow = (win_window*)window;
	SwapBuffers(wwindow->hdc);
}

#endif
