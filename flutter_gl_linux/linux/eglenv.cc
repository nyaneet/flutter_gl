
#include "include/eglenv.h"

// #include <EGL/egl.h>
// #include <EGL/eglext.h>
// #include "include/fl_my_texture_gl.h"
/*EglEnv::EglEnv(GdkWindow *window) {
//EglEnv::EglEnv(GdkGLContext* context) { //GdkWindow *window) {
  //  context_=context;//window_=window;
   window_=window;
}
*/
void EglEnv::setupRender(GdkWindow *window)
{
  g_autoptr(GError) error = nullptr;
  context_ = gdk_window_create_gl_context(window, &error);
  printf(".... eglenv setuprender \n"); //%ld\n",context_);
  if (error != nullptr)
    printf(".... setup render error\n");

  if (!gdk_gl_context_realize(
          context_,
          &error))
  {
    printf(".... setuprenderer realize false\n");
  }
  if (error != NULL)
  {
    printf(".... setuprenderer realize failed\n");
    g_clear_error(&error);
  }
}

void EglEnv::makeCurrent()
{
  gdk_gl_context_make_current(context_); // window_);
}

void EglEnv::dispose()
{
  // GdkSurface* surface = gdk_gl_context_get_surface(context_);
  // gdk_surface_destroy(&context_);
  // surface = nullptr;
  g_clear_object(&context_);
  gdk_gl_context_clear_current();
}
