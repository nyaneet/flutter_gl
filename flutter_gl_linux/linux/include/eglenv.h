#ifndef EGLENV_H
#define EGLENV_H


#include <flutter_linux/flutter_linux.h>

//#include "fl_my_texture_gl.h"

class EglEnv {
public:
    GdkGLContext* context_;
    EglEnv() {}
    void setupRender(GdkWindow *window);
    void makeCurrent();
    void dispose();
};

#endif