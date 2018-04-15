#include "Texture1D.hpp"


Texture1D::Texture1D()
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();
	
	ogl->glGenTextures(1, &textureId);
	
	ogl->glBindTexture(GL_TEXTURE_1D, textureId);
	
	ogl->glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	ogl->glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	ogl->glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	ogl->glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	ogl->glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	float bcolor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ogl->glTexParameterfv(GL_TEXTURE_1D, GL_TEXTURE_BORDER_COLOR, bcolor);
	
	ogl->glBindTexture(GL_TEXTURE_1D, 0);
	
	width = 0; 
}

void Texture1D::Allocate(uint64_t w)
{
	width = w;
	
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();

	ogl->glBindTexture(GL_TEXTURE_1D, textureId);

	ogl->glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA32F, width,
					  0, GL_RGBA, GL_FLOAT, NULL);
					  
	ogl->glBindTexture(GL_TEXTURE_1D, 0);
}

void Texture1D::Destroy()
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();

	ogl->glDeleteTextures(1, &textureId);
}

void Texture1D::LoadData(void* buffer)
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();

	ogl->glBindTexture(GL_TEXTURE_1D, textureId);
	ogl->glTexSubImage1D(GL_TEXTURE_1D, 0, 0, width, GL_RGBA, GL_FLOAT, buffer);
	ogl->glBindTexture(GL_TEXTURE_1D, 0);
}

unsigned int Texture1D::GetTextureId()
{
	return textureId; 
}

uint64_t Texture1D::Width()
{
	return width; 
}
