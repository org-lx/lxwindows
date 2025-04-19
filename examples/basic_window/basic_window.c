#include "lxwindows.h"
#include <stdio.h>

unsigned char icon_data[64 * 64 * 4];

int main(void) {
	lxw_init();

	for (int y = 0; y < 64; y++) {
    	for (int x = 0; x < 64; x++) {
        	int index = (y * 64 + x) * 4;
        	if ((x + y) % 2 == 0) {
                icon_data[index] = 0x00;    // Red
                icon_data[index + 1] = 0xFF; // Green
                icon_data[index + 2] = 0x00; // Blue
                icon_data[index + 3] = 0xFF; // Alpha (Opaque)
        	} else {
                icon_data[index] = 0xFF;    // Red
                icon_data[index + 1] = 0x00; // Green
                icon_data[index + 2] = 0xFF; // Blue
         	    icon_data[index + 3] = 0xFF; // Alpha (Opaque)
      	    }
   	    }
	}

	lxwindow window = lxw_create_window(1920, 1080, "Test Window");

	lxw_set_window_icon(window, (unsigned char*)icon_data, 32, 32);
	lxw_make_gl_context(window);

   const char* title = lxw_query_window_name(window);
   printf("Window Name > %s\n", title);

	int prev_width = 1920, prev_height = 1080;
	while (lxw_window_is_open(window)) {
       lxw_process_window(window);

       glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
       glClear(GL_COLOR_BUFFER_BIT);

       lxw_swap_buffers(window);
    }

	lxw_destroy_window(window);
}
