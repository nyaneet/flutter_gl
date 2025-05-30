#include "flutter_gl_linux/flutter_gl_linux_plugin.h"
#include "fl_my_texture_gl.h"
#include <flutter_linux/flutter_linux.h>

#include <iostream>

#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#include <gdk/gdktypes.h>
#include <GL/glew.h>
// #include <GL/glut.h>
// #include <GL/gl.h>
#include <EGL/egl.h>
// #include <EGL/eglext.h>
// #include <GLES2/gl2.h>
// // #define GLFW_INCLUDE_ES2
// // #include <GLFW/glfw3.h>
// // #include <GL/gl.h>
// #include <X11/X.h>
// #include <X11/Xlib.h>




void drawFrame(FlutterGlLinuxPlugin *self);
void main2(FlutterGlLinuxPlugin *self, int width, int height);
// void main3(FlutterGlLinuxPlugin *self, int width, int height);
void mainFBO(FlutterGlLinuxPlugin *self, int width, int height);
void mainFBO2(FlutterGlLinuxPlugin *self, int width, int height);
void mainFBO3(FlutterGlLinuxPlugin *self, int width, int height);
void mainFBO4(FlutterGlLinuxPlugin *self, int width, int height);
void mainFBO5(FlutterGlLinuxPlugin *self, int width, int height);
void eglTest(EGLDisplay egl_display = 0);

GLint common_get_shader_program(const char *vertex_shader_source, const char *fragment_shader_source);
