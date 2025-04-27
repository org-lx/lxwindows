#include "lxwindows.h"

#ifdef LXW_USE_X11
#include "x11_window.h"
#include <X11/extensions/XKB.h>
#include "internal.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int lxw_init() {
	_lxw_window_initilize_creation_data();
	return 1;
}

lxwindow lxw_create_window(int width, int height, const char* name) {
	x11_window* window = (x11_window*)malloc(sizeof(x11_window));

	window->display = XOpenDisplay(NULL);
	assert(window->display != NULL);

	int screen = DefaultScreen(window->display);

#ifdef LXW_USE_EGL
	window->egl_display = eglGetDisplay((EGLNativeDisplayType)window->display);
	assert(window->egl_display != EGL_NO_DISPLAY);

	EGLint egl_major, egl_minor;
	eglInitialize(window->egl_display, &egl_major, &egl_minor);

	eglBindAPI(EGL_OPENGL_API);

	const EGLint config_attribs[] = {
		EGL_RED_SIZE, _lxw_window_creation_data.red_size,
		EGL_GREEN_SIZE, _lxw_window_creation_data.green_size,
		EGL_BLUE_SIZE, _lxw_window_creation_data.blue_size,
		//EGL_ALPHA_SIZE, _lxw_window_creation_data.alpha_size,
		EGL_DEPTH_SIZE, _lxw_window_creation_data.depth_size,
		EGL_STENCIL_SIZE, _lxw_window_creation_data.stencil_size,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
		EGL_CONFORMANT, EGL_OPENGL_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE
	};

	EGLint num_configs;
	eglChooseConfig(window->egl_display, config_attribs, &window->config, 1, &num_configs);
	assert(num_configs>0);

	EGLint visual_id;
	eglGetConfigAttrib(window->egl_display, window->config, EGL_NATIVE_VISUAL_ID, &visual_id);

	XVisualInfo visual_template = {
		.visualid = visual_id
	};

	int num_visuals;
	window->vi = XGetVisualInfo(window->display, VisualIDMask, &visual_template, &num_visuals);
	assert(window->vi != NULL && num_visuals > 0);
	int root_depth = DefaultDepth(window->display, screen);
	if (window->vi->depth != root_depth) {
	    fprintf(stderr, "Depth mismatch: Visual %d vs Root %d\n",
	            window->vi->depth, root_depth);
	}
#elif defined(LXW_USE_GLX)
	int glx_attr[] = { 	GLX_RGBA,
								GLX_RED_SIZE, _lxw_window_creation_data.red_size,
								GLX_GREEN_SIZE, _lxw_window_creation_data.green_size,
								GLX_BLUE_SIZE, _lxw_window_creation_data.blue_size,
								GLX_ALPHA_SIZE, _lxw_window_creation_data.alpha_size,
								GLX_DEPTH_SIZE, _lxw_window_creation_data.depth_size,
								GLX_STENCIL_SIZE, _lxw_window_creation_data.stencil_size,
								GLX_DOUBLEBUFFER, None };
	window->vi = glXChooseVisual(window->display, screen, glx_attr);
	assert(window->vi != NULL);
#endif

	XSetWindowAttributes swa;
	swa.colormap = XCreateColormap(window->display, RootWindow(window->display, screen), window->vi->visual, AllocNone);
	swa.event_mask = ExposureMask | KeyPressMask;

	window->window = XCreateWindow(
			window->display,
			RootWindow(window->display, screen),
			0,
			0,
			width,
			height,
			0,
			window->vi->depth,
			InputOutput,
			window->vi->visual,
			CWColormap | CWEventMask,
			&swa);

	XStoreName(window->display, window->window, name);

	window->delete_message = XInternAtom(window->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(window->display, window->window, &window->delete_message, 1);

	XMapWindow(window->display, window->window);
	XAutoRepeatOn(window->display);
	XSelectInput(window->display, window->window, StructureNotifyMask | KeyPressMask | KeyReleaseMask);

	window->width = width;
	window->height = height;
	window->details += 0b10000000;

	return (lxwindow)window;
}

void lxw_process_window(lxwindow window) {
	x11_window* xwindow = (x11_window*)window;
	XEvent event;

	while (XPending(xwindow->display)) {
		XNextEvent(xwindow->display, &event);

		KeyCode keycode = event.xkey.keycode;
		switch (event.type) {
			case ClientMessage:
				if ((Atom)event.xclient.data.l[0] == xwindow->delete_message) {
					xwindow->details = 0;
				}
				break;

			case ConfigureNotify:
				if (event.xconfigure.width != xwindow->width || event.xconfigure.height != xwindow->height) {
					xwindow->width = event.xconfigure.width;
					xwindow->height = event.xconfigure.height;
					glViewport(0, 0, xwindow->width, xwindow->height);
				}
				break;

			case KeyPress:
				if (keycode >= 0 && keycode <= 255) {
					xwindow->key_states[XLookupKeysym(&event.xkey, 0)] = (event.type == KeyPress) ? 1 : 0;
				}
				break;
			case KeyRelease:
				if (keycode >= 0 && keycode <= 255) {
					XEvent next_event;
					XPeekEvent(xwindow->display, &next_event);
					if (next_event.type == KeyPress &&
							next_event.xkey.keycode == event.xkey.keycode) {
						xwindow->key_states[XLookupKeysym(&event.xkey, 0)] = 1;
					} else {
						xwindow->key_states[XLookupKeysym(&event.xkey, 0)] = 0;
					}
				}
				break;
			default:
				break;
		}
	}
}

int lxw_window_is_open(lxwindow window) {
	x11_window* xwindow = (x11_window*)window;
	return xwindow->details & 0b1;
}

void lxw_destroy_window(lxwindow window) {
	x11_window* xwindow = (x11_window*)window;

#ifdef LXW_USE_EGL
	if (xwindow->details & 0b01) {
		eglMakeCurrent(xwindow->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroyContext(xwindow->egl_display, xwindow->context);
		eglDestroySurface(xwindow->egl_display, xwindow->surface);
	}
	eglTerminate(xwindow->egl_display);
#elif defined(LXW_USE_GLX)
	if (xwindow->details & 0b01) {
		glXMakeCurrent(xwindow->display, None, NULL);
		glXDestroyContext(xwindow->display, xwindow->context);
	}
#endif
	
	XDestroyWindow(xwindow->display, xwindow->window);
	XCloseDisplay(xwindow->display);
	free(xwindow);
}

void lxw_make_gl_context(lxwindow window) {
	x11_window* xwindow = (x11_window*)window;

#ifdef LXW_USE_EGL
	EGLint attr[] = {
		EGL_GL_COLORSPACE, EGL_GL_COLORSPACE_LINEAR,
		EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
		EGL_NONE
	};
	xwindow->surface = eglCreateWindowSurface(
		xwindow->egl_display,
		xwindow->config,
		(EGLNativeWindowType)xwindow->window,
		attr
	);
	assert(xwindow->surface != EGL_NO_SURFACE);

	const EGLint context_attribs[] = {
		EGL_CONTEXT_MAJOR_VERSION, (uint32_t)_lxw_window_creation_data.opengl_major,
		EGL_CONTEXT_MINOR_VERSION, (uint32_t)_lxw_window_creation_data.opengl_minor,
		EGL_CONTEXT_OPENGL_PROFILE_MASK, _lxw_window_creation_data.profile,
		EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE, EGL_TRUE,
		EGL_NONE
	};

	xwindow->context = eglCreateContext(
		xwindow->egl_display,
		xwindow->config,
		EGL_NO_CONTEXT,
		context_attribs
	);
	assert(xwindow->context != EGL_NO_CONTEXT);

	eglMakeCurrent(
		xwindow->egl_display,
		xwindow->surface,
		xwindow->surface,
		xwindow->context
	);

#elif defined(LXW_USE_GLX)
	xwindow->context = glXCreateContext(xwindow->display, xwindow->vi, NULL, GL_TRUE);
	glXMakeCurrent(xwindow->display, xwindow->window, xwindow->context);
#endif

	xwindow->details |= 0b01;
}

void lxw_swap_buffers(lxwindow window) {
	x11_window* xwindow = (x11_window*)window;
#ifdef LXW_USE_EGL
	eglSwapBuffers(xwindow->egl_display, xwindow->surface);
	eglWaitClient();
#elif defined(LXW_USE_GLX)
	glXSwapBuffers(xwindow->display, xwindow->window);
	glXWaitGL();
#endif
}

#endif
