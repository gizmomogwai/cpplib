#ifndef _OglTools_h_
#define _OglTools_h_

#include <windowsinclude.h>

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
		if (err != GL_NO_ERROR) {
			throw(Exception((const char*)gluErrorString(err), file, line));
		}
    return(err == GL_NO_ERROR);
	}

};

#endif 
