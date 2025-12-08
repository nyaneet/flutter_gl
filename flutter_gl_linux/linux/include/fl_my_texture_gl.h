#ifndef FLUTTER_MY_TEXTURE_H
#define FLUTTER_MY_TEXTURE_H

#include "fluttercommon.h"
#include "flutter_gl_linux/flutter_gl_linux_plugin.h"
#include "customrender.h"
#include <flutter_linux/flutter_linux.h>
#include <map>
#include <memory>

G_DECLARE_FINAL_TYPE(FlMyTextureGL,
                     fl_my_texture_gl,
                     FL,
                     MY_TEXTURE_GL,
                     FlTextureGL)

struct _FlMyTextureGL
{
  // FlTextureGL
  FlPixelBufferTexture parent_instance;
  uint32_t target;
  uint32_t name;
  uint32_t width;
  uint32_t height;
};

#define FLUTTER_GL_LINUX_PLUGIN(obj)                                     \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), flutter_gl_linux_plugin_get_type(), \
                              FlutterGlLinuxPlugin))

struct _FlutterGlLinuxPlugin
{
  GObject parent_instance;
  // GdkGLContext *context = nullptr;
  FlTextureRegistrar *texture_registrar = nullptr;
  FlView *fl_view = nullptr;
  GdkWindow *window = nullptr; // glenn
  uint32_t width = 0;          // glenn
  uint32_t height = 0;         // glenn
  // CustomRender *render = nullptr;
  std::map<int64_t, CustomRender*> *renders_ = nullptr;
};

FlMyTextureGL *fl_my_texture_gl_new(uint32_t target,
                                    uint32_t name,
                                    uint32_t width,
                                    uint32_t height);
#endif // FLUTTER_MY_TEXTURE_H
