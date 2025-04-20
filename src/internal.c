#include "internal.h"
#include "lxwindows.h"

lxw_window_creation_data _lxw_window_creation_data;

void _lxw_window_initilize_creation_data() {
	_lxw_window_creation_data = (lxw_window_creation_data){
		.red_size = 8,
		.green_size = 8,
		.blue_size = 8,
		.alpha_size = 8,
		.depth_size = 24,
		.stencil_size = 8,
		.opengl_major = 4,
		.opengl_minor = 6
	};
}

void lxw_set_window_flag(int flag, int value) {
	switch (flag) {
		case(LXW_WINDOW_FLAG_RED_SIZE):
			_lxw_window_creation_data.red_size = value;
			break;
		case(LXW_WINDOW_FLAG_GREEN_SIZE):
			_lxw_window_creation_data.green_size = value;
			break;
		case(LXW_WINDOW_FLAG_BLUE_SIZE):
			_lxw_window_creation_data.blue_size = value;
			break;
		case(LXW_WINDOW_FLAG_ALPHA_SIZE):
			_lxw_window_creation_data.alpha_size = value;
			break;
		case(LXW_WINDOW_FLAG_DEPTH_SIZE):
			_lxw_window_creation_data.depth_size = value;
			break;
		case(LXW_WINDOW_FLAG_STENCIL_SIZE):
			_lxw_window_creation_data.stencil_size = value;
			break;
		case(LXW_WINDOW_FLAG_GL_MAJOR):
			_lxw_window_creation_data.opengl_major = value;
			break;
		case(LXW_WINDOW_FLAG_GL_MINOR):
			_lxw_window_creation_data.opengl_minor = value;
			break;
	}
}