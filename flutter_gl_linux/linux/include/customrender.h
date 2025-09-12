
#ifndef CUSTOMRENDER_H
#define CUSTOMRENDER_H

#include <flutter_linux/flutter_linux.h>
#include "renderworker.h"
#include "eglenv.h"
#include <memory>
#include "fl_my_texturep_gl.h"

class CustomRender
{
public:
  uint32_t width;
  uint32_t height;
  CustomRender(uint32_t width_, uint32_t height_, FlTextureRegistrar *texture_registrar, GdkWindow *window);
  GdkWindow *window_; // m_hWnd;
  RenderWorker renderWorker;
  FlTextureRegistrar *texture_registrar_;
  FlTexture *texture_;
  FlMyTexturePGL *myTexturep;
  void initEGL();
  void initGL();
  void dispose();
  FlValue *getEgls();
  int64_t texture_id() const { return texture_id_; }
  int updateTexture(GLuint sourceTexture);
  //  EglEnv shareEglEnv;
  static EglEnv *eglEnv;
  static EglEnv *dartEglEnv;
  GLuint frameBuffer = 0;
  GLuint colorRenderBuffer = 0;
  GLuint texture = 0;
private:
  int64_t texture_id_;
};

#endif