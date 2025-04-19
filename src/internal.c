#include "internal.h"

lxw_window_creation_data _lxw_window_creation_data;

void _lxw_window_initilize_creation_data() {
	_lxw_window_creation_data = (lxw_window_creation_data){
		.red_size = 8,
		.green_size = 8,
		.blue_size = 8,
		.alpha_size = 8,
		.depth_size = 24,
		.stencil_size = 8
	};
}
