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

enum lxw_window_flag {
	lxw_window_flag_none = 0,
	lxw_window_flag_rgba = 1,
	lxw_window_flag_rgb = 2,
	lxw_window_flag_depth_size = 4,
	lxw_window_flag_gl_major = 8,
	lxw_window_flag_gl_minor = 16,
	lxw_window_flag_enable_experimental = 32
};

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
LXW_FUNC char* lxw_query_window_name(lxwindow);
LXW_FUNC void lxw_query_window_min_size(lxwindow, int* mw, int* mh);

// set info about the window
LXW_FUNC void lxw_set_window_size(lxwindow, int w, int h);
LXW_FUNC void lxw_set_window_pos(lxwindow, int x, int y);
LXW_FUNC void lxw_set_window_name(lxwindow, char* name);
LXW_FUNC void lxw_set_window_min_size(lxwindow, int mw, int mh);
LXW_FUNC void lxw_set_window_icon(lxwindow, unsigned char* data, int w, int h);

// multiple windows stuff
LXW_FUNC lxwindow lxw_get_window_by_name(char*);

// internal use only
LXW_FUNC void _lxw_add_window(lxwindow, char*);

/***************
 *             *
 *    INPUT    *
 *             *
 ***************/

#include "keycodes.h"

LXW_FUNC int lxw_get_key_state(lxwindow, char key);
