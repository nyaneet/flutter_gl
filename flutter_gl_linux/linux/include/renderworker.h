

#ifndef RENDERWORKER_H
#define RENDERWORKER_H

#include "fluttercommon.h"
#include "OpenGLProgram.h"
#include <flutter_linux/flutter_linux.h>

class RenderWorker {
public:
   // RenderWorker();
  void setup();
   // int64_t vertexBuffer = 0;
    GLuint vertexBuffer = 0;
    GLuint program = 0;
    GLuint getProgram();
    OpenGLProgram openGLProgram;
    int renderTexture(GLuint sourceTexture);//, bool isFBO);
    int drawTexture(GLuint texture, GLuint vertexBuffer_);
    void dispose();
private:
  void setupVBO();
};

#endif