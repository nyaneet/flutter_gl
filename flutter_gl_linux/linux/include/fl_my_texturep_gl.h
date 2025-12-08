#ifndef FLUTTER_MY_TEXTUREP_H
#define FLUTTER_MY_TEXTUREP_H

#include "fluttercommon.h"
#include "flutter_gl_linux/flutter_gl_linux_plugin.h"
#include <flutter_linux/flutter_linux.h>

G_DECLARE_FINAL_TYPE(FlMyTexturePGL,
                     fl_my_texturep_gl,
                     FL,
                     MY_TEXTUREP_GL,
                     FlPixelBufferTexture)

struct _FlMyTexturePGL
{
    FlPixelBufferTexture parent_instance;

    uint8_t *buffer;
    uint32_t width;// = self->width;
    uint32_t height;;// = self->height;
};


FlMyTexturePGL *fl_my_texturep_gl_new(uint32_t width,
                                      uint32_t height);//uint8_t *buffer
                                 //   );
#endif // FLUTTER_MY_TEXTUREP_H
