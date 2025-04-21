# LXWindows
Dependincy free windowing library written in c99 with support for X11, Windows, and Wayland

LXWindows has an easy to use api with support for EGL, GLX, and WGL

## Features

### Windowing
Create a window in 2 lines of code

```
// create a 1280x720 window with the name "very cool window"
lxw_init();
lxw_window window = lxw_create_window(1280, 720, "very cool window");
```

### OpenGL Support
```
// call lxw_make_gl_context to create a opengl context and set it as the default
lxw_make_gl_context(window);
```
note that to load any functions passed 1.0, you need an external opengl loader like GLEW or GLAD

### Input
```
// get state of the key 'a'
uint8_t a_status = lxw_get_key_state(window, LXW_a);
```

You can see a full example of LXWindows in [examples/basic_window](https://github.com/org-lx/lxwindows/blob/main/examples/basic_window/basic_window.c)
