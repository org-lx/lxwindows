#pragma once

#include "lxwindows.h"

#include <Windows.h>
#include <gl/GL.h>

#ifdef LXW_USE_EGL
#include <EGL/egl.h>
#endif

typedef struct {
	HWND hwnd;
	HDC hdc;
	MSG msg;

	int width;
	int height;

	unsigned char running;
	unsigned char has_context;

#ifdef LXW_USE_WGL
	HGLRC hglrc;
#elif defined(LXW_USE_EGL)
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	EGLConfig config;
#endif

} win_window;
