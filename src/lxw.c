#include "lxwindows.h"

#include <stdlib.h>

lxwindow* windows;
char** names;
int num_windows;

lxwindow lxw_get_window_by_name(char* name) {
	for (int i = 0; i < num_windows; ++i) {
		if (names[i] == name) {
			return windows[i];
		}
	}
	return (int*)0x0;
}

void _lxw_add_window(lxwindow window, char* name) {
	num_windows++;
	windows = realloc(windows, num_windows*sizeof(lxwindow));
	names = realloc(names, num_windows*sizeof(char*));

	windows[num_windows-1] = window;
	names[num_windows-1] = name;
}
