#include <GL/glew.h>
#include "lxwindows.h"

#include <stdio.h>

unsigned char icon_data[64 * 64 * 4];

const char* vertex_shader = 
"#version 330 core\n"
"layout(location = 0) in vec2 pos;"
"out vec2 uv;"
"void main() {"
"	gl_Position = vec4(pos, 0, 1);"
"	uv = pos/2.0 + 0.5;"
"}\0";

const char* fragment_shader = 
"#version 330 core\n"
"in vec2 uv;"
"out vec4 color;"
"void main() {"
"	color = vec4(uv, 0.3f,1);"
"}\0";

const float quad_vertices[12] = {
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	-0.5f,  0.5f,
	 0.5f, -0.5f,
	-0.5f,  0.5f,
	 0.5f,  0.5f,
};

int main(void) {
	lxw_init();

	for (int y = 0; y < 64; y++) {
		for (int x = 0; x < 64; x++) {
			int index = (y * 64 + x) * 4;
			if ((x + y) % 2 == 0) {
				icon_data[index] = 0x00;	// Red
				icon_data[index + 1] = 0xFF; // Green
				icon_data[index + 2] = 0x00; // Blue
				icon_data[index + 3] = 0xFF; // Alpha (Opaque)
			} else {
				icon_data[index] = 0xFF;	// Red
				icon_data[index + 1] = 0x00; // Green
				icon_data[index + 2] = 0xFF; // Blue
		 		icon_data[index + 3] = 0xFF; // Alpha (Opaque)
	  		}
   		}
	}

	lxw_set_window_flag(LXW_WINDOW_FLAG_PROFILE_CORE,1);
	lxw_set_window_flag(LXW_WINDOW_FLAG_GL_MAJOR,4);
	lxw_set_window_flag(LXW_WINDOW_FLAG_GL_MINOR,6);
	lxwindow window = lxw_create_window(1920, 1080, "Test Window");

	lxw_set_window_icon(window, (unsigned char*)icon_data, 32, 32);
	lxw_make_gl_context(window);

	glewInit();

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_shader, NULL);
	glCompileShader(vertex);
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_shader, NULL);
	glCompileShader(fragment);
	
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	unsigned int vbo,vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW); 

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	printf("OpenGL Version %d.%d is in use\n",major,minor);

	float r = 0.2f;
	while (lxw_window_is_open(window)) {
	   lxw_process_window(window);

		if (lxw_get_key_state(window, LXW_w)) {
			r += 0.01f;
		} else if (lxw_get_key_state(window, LXW_s)) {
			r -= 0.01f;
		}

		int w,h;
		lxw_query_window_size(window, &w, &h);
		glViewport(0, 0, w, h);


	   glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
	   glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);

	   lxw_swap_buffers(window);
	}

	lxw_destroy_window(window);
}
