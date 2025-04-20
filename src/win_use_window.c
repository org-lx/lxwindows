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
	win_window* window = (win_window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

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
	memset(window, 0, sizeof(win_window));

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
	free(wtitle);
	assert(window->hwnd != NULL);

	window->hdc = GetDC(window->hwnd);

#ifdef LXW_USE_WGL
   int sum =   _lxw_window_creation_data.red_size +
               _lxw_window_creation_data.green_size +
               _lxw_window_creation_data.blue_size;

	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = sum;
	pfd.cRedBits = _lxw_window_creation_data.red_size;
	pfd.cGreenBits = _lxw_window_creation_data.green_size;
	pfd.cBlueBits = _lxw_window_creation_data.blue_size;
	pfd.cAlphaBits = _lxw_window_creation_data.alpha_size;
	pfd.cDepthBits = _lxw_window_creation_data.depth_size;
	pfd.cStencilBits = _lxw_window_creation_data.stencil_size;

	int pixelFormat = ChoosePixelFormat(window->hdc, &pfd);
	SetPixelFormat(window->hdc, pixelFormat, &pfd);
#elif defined(LXW_USE_EGL)
	window->display = eglGetDisplay(window->hdc);
	assert(window->display != EGL_NO_DISPLAY);

	EGLint major, minor;
	if (!eglInitlize(window->display, &major, &minor)) {
		assert(0 && "Failed to initilize EGL");
	}

	EGLint attribs[] = {
		EGL_RED_SIZE, _lxw_window_creation_data.red_size,
		EGL_GREEN_SIZE, _lxw_window_creation_data.green_size,
		EGL_BLUE_SIZE, _lxw_window_creation_data.blue_size,
		EGL_ALPHA_SIZE, _lxw_window_creation_data.alpha_size,
		EGL_DEPTH_SIZE, _lxw_window_creation_data.depth_size,
		EGL_STENCIL_SIZE, _lxw_window_creation_data.stencil_size,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
		EGL_NONE
	};

	EGLint numConfigs;
	if (!eglChooseConfig(window->display, attribs, &window->config, 1, &numConfigs)) {
		assert(0 && "Failed to choose EGL config");
	}

	window->surface = eglCreateWindowSurface(window->display, window->config, window->hwnd, NULL);
	assert(window->surface != EGL_NO_SURFACE);
#endif

	ShowWindow(window->hwnd, SW_SHOW);
	UpdateWindow(window->hwnd);

	window->width = width;
	window->height = height;
	window->running = 1;
	
	SetWindowLongPtr(window->hwnd, GWLP_USERDATA, (long long)window);

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

#ifdef LXW_USE_WGL
	SwapBuffers(wwindow->hdc);
#elif defined(LXW_USE_EGL)
	eglSwapBuffers(wwindow->display, wwindow->surface);
#endif
}

#endif
