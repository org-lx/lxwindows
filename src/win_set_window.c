#include "lxwindows.h"

#ifdef LXW_USE_WINDOWS
#include "win_window.h"

#include <assert.h>

void lxw_set_window_size(lxwindow window, int w, int h) {
	win_window* wwindow = (win_window*)window;
	SetWindowPos(wwindow->hwnd, NULL, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
}

void lxw_set_window_pos(lxwindow window, int x, int y) {
	win_window* wwindow = (win_window*)window;
	SetWindowPos(wwindow->hwnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void lxw_set_window_name(lxwindow window, char* name) {
	win_window* wwindow = (win_window*)window;
	SetWindowText(wwindow->hwnd, name);
}

void lxw_set_window_icon(lxwindow window, unsigned char* data, int w, int h) {
	win_window* wwindow = (win_window*)window;
	BITMAPV5HEADER bi = {
		.bV5Size = sizeof(BITMAPV5HEADER),
		.bV5Width = w,
		.bV5Height = -h,
		.bV5Planes = 1,
		.bV5BitCount = 32,
		.bV5Compression = BI_BITFIELDS,
		.bV5RedMask = 0x00FF0000,
		.bV5GreenMask = 0x0000FF00,
		.bV5BlueMask = 0x000000FF,
		.bV5AlphaMask = 0xFF000000
	};

	void* pBits;
	HBITMAP hBitmap = CreateDIBSection(wwindow->hdc, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &pBits, NULL, 0);
	assert(hBitmap != NULL);

	memcpy(pBits, data, w * h * 4);
	HBITMAP hMask = CreateBitmap(w, h, 1, 1, NULL);

	ICONINFO ii = {
		.fIcon = TRUE,
		.hbmColor = hBitmap,
		.hbmMask = hMask
	};

	HICON hIcon = CreateIconIndirect(&ii);

	DeleteObject(hBitmap);
	DeleteObject(hMask);
	
	if (hIcon) {
		SendMessage(wwindow->hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		SendMessage(wwindow->hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	}
}

#endif
