#pragma once

#define LXW_FUNC

#ifdef __linux
#define LXW_USE_X11
#endif
#ifdef _WIN32
#define LXW_USE_WINDOWS
#include <Windows.h>
#undef LXW_FUNC
#define LXW_FUNC __declspec(dllexport)
#endif

#if !defined(LXW_USE_EGL) && !defined(LXW_USE_GLX) && defined(LXW_USE_X11)
#define LXW_USE_EGL
#endif

#if !defined(LXW_USE_EGL) && !defined(LXW_USE_WGL) && defined(LXW_USE_WINDOWS)
#define LXW_USE_EGL
#endif

#include <GL/gl.h>

typedef void* lxwindow;

LXW_FUNC int lxw_init();

/*********************
 *                   *
 *     WINDOWING     *
 *                   *
 *********************/

#define LXW_WINDOW_FLAG_RED_SIZE 					1
#define LXW_WINDOW_FLAG_GREEN_SIZE 					2
#define LXW_WINDOW_FLAG_BLUE_SIZE 					3
#define LXW_WINDOW_FLAG_ALPHA_SIZE 					4
#define LXW_WINDOW_FLAG_DEPTH_SIZE  				6
#define LXW_WINDOW_FLAG_STENCIL_SIZE  				6
#define LXW_WINDOW_FLAG_GL_MAJOR 					7
#define LXW_WINDOW_FLAG_GL_MINOR						8

LXW_FUNC void lxw_set_window_flag(int flag, int value);
LXW_FUNC lxwindow lxw_create_window(int width, int height, const char* name);
LXW_FUNC void lxw_process_window(lxwindow);
LXW_FUNC int lxw_window_is_open(lxwindow);
LXW_FUNC void lxw_destroy_window(lxwindow);

// opengl specific stuff
LXW_FUNC void lxw_make_gl_context(lxwindow);
LXW_FUNC void lxw_swap_buffers(lxwindow);

// query info about the window
LXW_FUNC void lxw_query_window_size(lxwindow, int* w, int* h);
LXW_FUNC void lxw_query_window_pos(lxwindow, int* x, int* h);
LXW_FUNC const char* lxw_query_window_name(lxwindow);
LXW_FUNC void lxw_query_window_min_size(lxwindow, int* mw, int* mh);

// set info about the window
LXW_FUNC void lxw_set_window_size(lxwindow, int w, int h);
LXW_FUNC void lxw_set_window_pos(lxwindow, int x, int y);
LXW_FUNC void lxw_set_window_name(lxwindow, char* name);
LXW_FUNC void lxw_set_window_min_size(lxwindow, int mw, int mh);
LXW_FUNC void lxw_set_window_icon(lxwindow, unsigned char* data, int w, int h);

/***************
 *             *
 *    INPUT    *
 *             *
 ***************/

#include "keycodes.h"

LXW_FUNC int lxw_get_key_state(lxwindow, char key);
