#pragma once

#define LXW_FUNC

//#define LXW_USE_EGL
//#define LXW_USE_GLX
//#define LXW_USE_WGL

#ifdef __linux
	#define LXW_USE_X11
	#include <GL/gl.h>
#endif
#ifdef _WIN32
	#include <gl/GL.h>
	#define LXW_USE_WINDOWS
	#undef LXW_FUNC
	#define LXW_FUNC __declspec(dllexport)
#endif

#if !__has_include("EGL/egl.h")
	#ifdef __linux
		#define LXW_USE_GLX
	#elif defined(_WIN32)
		#define LXW_USE_WGL
	#endif
#endif

#if !defined(LXW_USE_EGL) && !defined(LXW_USE_GLX) && defined(LXW_USE_X11)
	#define LXW_USE_EGL
#endif

#if !defined(LXW_USE_EGL) && !defined(LXW_USE_WGL) && defined(LXW_USE_WINDOWS)
	#define LXW_USE_WGL
#endif



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
#define LXW_WINDOW_FLAG_STENCIL_SIZE  				7
#define LXW_WINDOW_FLAG_GL_MAJOR 					8
#define LXW_WINDOW_FLAG_GL_MINOR						9
#define LXW_WINDOW_FLAG_PROFILE_CORE				10
#define LXW_WINDOW_FLAG_PROFILE_COMPAT				11

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

#define LXW_A 'a'
#define LXW_B 'b'
#define LXW_C 'c'
#define LXW_D 'd'
#define LXW_E 'e'
#define LXW_F 'f'
#define LXW_G 'g'
#define LXW_H 'h'
#define LXW_I 'i'
#define LXW_J 'j'
#define LXW_K 'k'
#define LXW_L 'l'
#define LXW_M 'm'
#define LXW_N 'n'
#define LXW_O 'o'
#define LXW_P 'p'
#define LXW_Q 'q'
#define LXW_R 'r'
#define LXW_S 's'
#define LXW_T 't'
#define LXW_U 'u'
#define LXW_V 'v'
#define LXW_W 'w'
#define LXW_X 'x'
#define LXW_Y 'y'
#define LXW_Z 'z'

#define LXW_LEFT_MOUSE     0
#define LXW_RIGHT_MOUSE    1
#define LXW_CENTER_MOUSE   0

LXW_FUNC int lxw_get_key_state(lxwindow, char key);
