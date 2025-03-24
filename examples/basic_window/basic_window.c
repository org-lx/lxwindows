#include "lxwindows.h"

int main(void) {
	lxw_init();

	lxwindow window = lxw_create_window(1920, 1080, "Test Window");
	lxw_make_gl_context(window);
	

	while (lxw_window_is_open(window)) {
		lxw_process_window(window);

		glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		lxw_swap_buffers(window);
	}

	lxw_destroy_window(window);
}
