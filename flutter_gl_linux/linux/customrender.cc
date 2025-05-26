
#include "include/customrender.h"
#include <flutter_linux/fl_pixel_buffer_texture.h>
#include <flutter_linux/fl_texture_registrar.h>

static FlTextureRegistrar *texture_registrar_;
static FlTexture *texture_;
static FlMyTexturePGL *myTexturep;

CustomRender::CustomRender(uint32_t width_, uint32_t height_, FlTextureRegistrar *texture_registrar, GdkWindow *window)

{
    texture_registrar_ = texture_registrar;
    window_ = window;
    width = width_;
    height = height_;
    printf(".... customrender create  %d\n", width);
    myTexturep = fl_my_texturep_gl_new(width, height);
    texture_ = FL_TEXTURE(myTexturep);
    fl_texture_registrar_register_texture(texture_registrar_, texture_);
    texture_id_ = fl_texture_get_id(texture_);
    initEGL();
}

FlValue *CustomRender::getEgls()
{
    g_autoptr(FlValue) fl_vector = fl_value_new_list();
    fl_value_append(fl_vector, fl_value_new_int(0));
    fl_value_append(fl_vector, fl_value_new_int(0));
    // eglEnv.window
    fl_value_append(fl_vector, fl_value_new_int(reinterpret_cast<int64_t>(eglEnv.context_))); // context_)));
    fl_value_append(fl_vector, fl_value_new_int(0));
    fl_value_append(fl_vector, fl_value_new_int(0));
    // dartEglEnv.window
    fl_value_append(fl_vector, fl_value_new_int(reinterpret_cast<int64_t>(dartEglEnv.context_))); // context_)));
    return fl_value_ref(fl_vector);
}

void CustomRender::initEGL()
{
    printf(".... initEGL\n");
    eglEnv = EglEnv();
    dartEglEnv = EglEnv();
    printf(".... initegl eglenv setup\n");
    eglEnv.setupRender(window_);
    printf(".... initegl darteglenv setup\n");
    dartEglEnv.setupRender(window_);
    eglEnv.makeCurrent();
    initGL();
    renderWorker = RenderWorker();
    renderWorker.setup();
}

void CustomRender::initGL()
{
    printf(".... initGL %d\n", width);
    glViewport(0, 0, GLsizei(width), GLsizei(height));

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GLenum(GL_FRAMEBUFFER), frameBuffer);

    GLuint texture = 0;
    glGenTextures(1, &texture);

    printf("initGL, generate texture, id %ld \n\n", texture);

    glBindTexture(GLenum(GL_TEXTURE_2D), texture);
    glTexParameteri(GLenum(GL_TEXTURE_2D), GLenum(GL_TEXTURE_MAG_FILTER), GL_LINEAR);
    glTexParameteri(GLenum(GL_TEXTURE_2D), GLenum(GL_TEXTURE_MIN_FILTER), GL_LINEAR);

    glTexImage2D(GLenum(GL_TEXTURE_2D), 0, GLenum(GL_RGBA), GLsizei(width), GLsizei(height), 0, GLenum(GL_RGBA),
                 GLenum(GL_UNSIGNED_BYTE), NULL);

    GLuint colorRenderBuffer = 0;
    glGenRenderbuffers(1, &colorRenderBuffer);
    glBindRenderbuffer(GLenum(GL_RENDERBUFFER), colorRenderBuffer);
    glRenderbufferStorage(GLenum(GL_RENDERBUFFER), GLenum(GL_DEPTH24_STENCIL8), GLsizei(width), GLsizei(height));

    glFramebufferTexture2D(GLenum(GL_FRAMEBUFFER), GLenum(GL_COLOR_ATTACHMENT0), GLenum(GL_TEXTURE_2D), texture, 0);

    glFramebufferRenderbuffer(GLenum(GL_FRAMEBUFFER), GLenum(GL_DEPTH_ATTACHMENT), GLenum(GL_RENDERBUFFER), colorRenderBuffer);
    glFramebufferRenderbuffer(GLenum(GL_FRAMEBUFFER), GLenum(GL_STENCIL_ATTACHMENT), GLenum(GL_RENDERBUFFER), colorRenderBuffer);
    printf(".... initGL exit %d\n", width);
}

int CustomRender::updateTexture(GLuint sourceTexture)
{
    printf("custom render, updateTexture, id: %ld", sourceTexture);

    eglEnv.makeCurrent();
    glBindFramebuffer(GLenum(GL_FRAMEBUFFER), frameBuffer);

    glClearColor(GLclampf(0.0), GLclampf(0.0), GLclampf(0.0), GLclampf(0.0));
    glClear(GLbitfield(GL_COLOR_BUFFER_BIT));

    int data = renderWorker.renderTexture(sourceTexture);
    uint8_t *buffer = myTexturep->buffer;
    glReadPixels(0, 0, GLsizei(width), GLsizei(height), GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    fl_texture_registrar_mark_texture_frame_available(texture_registrar_, texture_);
    return data;
}

void CustomRender::deleteTexture(GLuint textureId)
{
    printf("custom render, deleteTexture, id: %ld\n", textureId);
    glDeleteTextures(1, &textureId);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("*** OpenGL error after delete texture: 0x%08x ***\n", error);
    }
}