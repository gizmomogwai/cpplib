#ifndef _OglTools_h_
#define _OglTools_h_

#include <lang/Exception.h>

#ifdef OSX
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

class OglTools {

public:
  bool static checkOglState(char* file, int line) throw (Exception) {
    GLenum err = glGetError();
    switch (err) {
    case GL_NO_ERROR:
      break;
    case GL_INVALID_ENUM:
      throw Exception("GL_INVALID_ENUM");
    case GL_INVALID_VALUE:
      throw Exception("GL_INVALID_VALUE");
    case GL_INVALID_OPERATION:
      throw Exception("GL_INVALID_OPERATION");
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      throw Exception("GL_INVALID_FRAMEBUFFER_OPERATION");
    case GL_OUT_OF_MEMORY:
      throw Exception("GL_OUT_OF_MEMORY");
    case GL_STACK_UNDERFLOW:
      throw Exception("GL_STACK_UNDERFLOW");
    case GL_STACK_OVERFLOW:
      throw Exception("GL_STACK_OVERFLOW");
    default:
      throw Exception("Unknown ogl error");
    }
    return(err == GL_NO_ERROR);
  }

};

#endif
