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

#include <GL/gl.h>

typedef void* lxwindow;

LXW_FUNC int lxw_init();

/*********************
 *                   *
 *     WINDOWING     *
 *                   *
 *********************/

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
LXW_FUNC char* lxw_query_window_name(lxwindow);

// set info about the window
LXW_FUNC void lxw_set_window_size(lxwindow, int w, int h);
LXW_FUNC void lxw_set_window_pos(lxwindow, int x, int y);
LXW_FUNC void lxw_set_window_name(lxwindow, char* name);

/***************
 *             *
 *    INPUT    *
 *             *
 ***************/

#include "keycodes.h"

LXW_FUNC int lxw_get_key_state(lxwindow, char key);
