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

#define LXW_space                         0x0020
#define LXW_exclam                        0x0021
#define LXW_quotedbl                      0x0022
#define LXW_numbersign                    0x0023
#define LXW_dollar                        0x0024
#define LXW_percent                       0x0025
#define LXW_ampersand                     0x0026
#define LXW_apostrophe                    0x0027
#define LXW_parenleft                     0x0028
#define LXW_parenright                    0x0029
#define LXW_asterisk                      0x002a
#define LXW_plus                          0x002b
#define LXW_comma                         0x002c
#define LXW_minus                         0x002d
#define LXW_period                        0x002e
#define LXW_slash                         0x002f
#define LXW_0                             0x0030
#define LXW_1                             0x0031
#define LXW_2                             0x0032
#define LXW_3                             0x0033
#define LXW_4                             0x0034
#define LXW_5                             0x0035
#define LXW_6                             0x0036
#define LXW_7                             0x0037
#define LXW_8                             0x0038
#define LXW_9                             0x0039
#define LXW_colon                         0x003a
#define LXW_semicolon                     0x003b
#define LXW_less                          0x003c
#define LXW_equal                         0x003d
#define LXW_greater                       0x003e
#define LXW_question                      0x003f
#define LXW_at                            0x0040
#define LXW_A                             0x0041
#define LXW_B                             0x0042
#define LXW_C                             0x0043
#define LXW_D                             0x0044
#define LXW_E                             0x0045
#define LXW_F                             0x0046
#define LXW_G                             0x0047
#define LXW_H                             0x0048
#define LXW_I                             0x0049
#define LXW_J                             0x004a
#define LXW_K                             0x004b
#define LXW_L                             0x004c
#define LXW_M                             0x004d
#define LXW_N                             0x004e
#define LXW_O                             0x004f
#define LXW_P                             0x0050
#define LXW_Q                             0x0051
#define LXW_R                             0x0052
#define LXW_S                             0x0053
#define LXW_T                             0x0054
#define LXW_U                             0x0055
#define LXW_V                             0x0056
#define LXW_W                             0x0057
#define LXW_X                             0x0058
#define LXW_Y                             0x0059
#define LXW_Z                             0x005a
#define LXW_bracketleft                   0x005b
#define LXW_backslash                     0x005c
#define LXW_bracketright                  0x005d
#define LXW_asciicircum                   0x005e
#define LXW_underscore                    0x005f
#define LXW_grave                         0x0060
#define LXW_a                             0x0061
#define LXW_b                             0x0062
#define LXW_c                             0x0063
#define LXW_d                             0x0064
#define LXW_e                             0x0065
#define LXW_f                             0x0066
#define LXW_g                             0x0067
#define LXW_h                             0x0068
#define LXW_i                             0x0069
#define LXW_j                             0x006a
#define LXW_k                             0x006b
#define LXW_l                             0x006c
#define LXW_m                             0x006d
#define LXW_n                             0x006e
#define LXW_o                             0x006f
#define LXW_p                             0x0070
#define LXW_q                             0x0071
#define LXW_r                             0x0072
#define LXW_s                             0x0073
#define LXW_t                             0x0074
#define LXW_u                             0x0075
#define LXW_v                             0x0076
#define LXW_w                             0x0077
#define LXW_x                             0x0078
#define LXW_y                             0x0079
#define LXW_z                             0x007a
#define LXW_braceleft                     0x007b
#define LXW_bar                           0x007c
#define LXW_braceright                    0x007d
#define LXW_asciitilde                    0x007e

#define LXW_LEFT_MOUSE     0
#define LXW_RIGHT_MOUSE    1
#define LXW_CENTER_MOUSE   2

LXW_FUNC uint8_t lxw_get_key_state(lxwindow, char key);
