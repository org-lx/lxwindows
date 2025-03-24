#pragma once
#include <GL/gl.h>

#ifdef __linux
#define LXW_USE_X11
#endif
#ifdef __WIN32
#define LXW_USE_WINDOWS
#endif

typedef void* lxwindow;

int lxw_init();

/*********************
 *                   *
 *     WINDOWING     *
 *                   *
 *********************/

lxwindow lxw_create_window(int width, int height, const char* name);
void lxw_process_window(lxwindow);
int lxw_window_is_open(lxwindow);
void lxw_destroy_window(lxwindow);

// opengl specific stuff
void lxw_make_gl_context(lxwindow);
void lxw_swap_buffers(lxwindow);

// query info about the window
void lxw_query_window_size(lxwindow, int* w, int* h);
void lxw_query_window_pos(lxwindow, int* x, int* h);
char* lxw_query_window_name(lxwindow);

// set info about the window
void lxw_set_window_size(lxwindow, int w, int h);
void lxw_set_window_pos(lxwindow, int x, int y);
void lxw_set_window_name(lxwindow, char* name);

/***************
 *             *
 *    INPUT    *
 *             *
 ***************/

#include "keycodes.h"

int lxw_get_key_state(lxwindow, char key);
