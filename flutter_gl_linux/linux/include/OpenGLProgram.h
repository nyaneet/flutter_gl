//#include <windows.h>
//#include <glad/glad.h>
#include "fluttercommon.h"

class OpenGLProgram {
    public:
        GLuint programHandle = 0;
        GLuint getProgram();
        GLuint compileShaders(char *vertex_shader, char *fragment_shader);
        unsigned int compileShader(char *shader, GLenum shaderType);
        unsigned int compileShaderCode(char *shaderCode, GLenum type);
        void dispose();
};