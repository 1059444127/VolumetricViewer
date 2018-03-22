#include "Texture3D.hpp"



Texture3D::Texture3D()
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();
	
	ogl->glGenTextures(1, &textureId);
	
	ogl->glBindTexture(GL_TEXTURE_3D, textureId);
	
	ogl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	ogl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	ogl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	ogl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	ogl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	ogl->glBindTexture(GL_TEXTURE_3D, 0);
}

void Texture3D::Allocate(uint64_t w, uint64_t h, uint64_t d)
{
	width = w;
	height = h;
	depth = d; 
	
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();

	ogl->glBindTexture(GL_TEXTURE_3D, textureId);
	
	ogl->glTexImage3D(GL_TEXTURE_3D, 0, GL_COMPRESSED_RGBA, width, height, depth,
								0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
								
	ogl->glBindTexture(GL_TEXTURE_3D, 0);
}

void Texture3D::Destroy()
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();

	ogl->glDeleteTextures(1, &textureId);
}

void Texture3D::LoadData(void* buffer, uint64_t count)
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();

	ogl->glBindTexture(GL_TEXTURE_3D, textureId);
	ogl->glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, width, height, depth, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	ogl->glBindTexture(GL_TEXTURE_3D, 0);
}
