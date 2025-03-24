#pragma once

#include <Windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>

typedef struct {
	HWND hwnd;
	HDC hdc;
	HGLRC hglrc;
	MSG msg;

	unsigned char running;
	unsigned char has_context;
} win_window;
