#include "Util.hpp"


void PrintGLErrors()
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();
	
	GLenum error = GL_NO_ERROR;
	do {
		error = ogl->glGetError();
		if (error != GL_NO_ERROR)
			std::cout << error <<  std::endl; 
	} while (error != GL_NO_ERROR);

}