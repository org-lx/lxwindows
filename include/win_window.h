#pragma once

#include <Windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>

typedef struct {
	HWND hwnd;
	HDC hdc;
	HGLRC hglrc;
	MSG msg;

	int width;
	int height;

	unsigned char running;
	unsigned char has_context;
} win_window;
