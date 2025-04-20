#pragma once
#include <stdint.h>

/// information about window creation
typedef struct lxw_window_creation_data {
	uint8_t red_size;
	uint8_t green_size;
	uint8_t blue_size;
	uint8_t alpha_size;
	uint8_t depth_size;
	uint8_t stencil_size;
	uint8_t opengl_major;
	uint8_t opengl_minor;
	uint8_t profile;
} lxw_window_creation_data;

extern lxw_window_creation_data _lxw_window_creation_data;
void _lxw_window_initilize_creation_data();
