#include "lxwindows.h"


#ifdef LXW_USE_X11
#include "x11_window.h"


uint8_t lxw_get_key_state(lxwindow window, char key) {
	return ((x11_window*)window)->key_states[key];
}

#endif
