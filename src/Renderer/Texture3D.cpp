#include "Texture3D.hpp"

#include <QtGui/QOpenGLFunctions>
#include <QOpenGLFunctions_3_2_Compatibility>


Texture3D::Texture3D()
{
	QOpenGLFunctions_3_2_Compatibility* ogl = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Compatibility>();
	
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
	QOpenGLFunctions_3_2_Compatibility* ogl = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Compatibility>();

	ogl->glBindTexture(GL_TEXTURE_3D, textureId);
	ogl->glCompressedTexImage3D(GL_TEXTURE_3D, 1, GL_RGBA8, width, height);
	ogl->glBindTexture(GL_TEXTURE_3D, 0);
}

void Texture3D::LoadData(void* buffer, uint64_t count)
{
	QOpenGLFunctions_3_2_Compatibility* ogl = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Compatibility>();

	ogl->glBindTexture(GL_TEXTURE_3D, textureId);
	ogl->glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, buffer);
	//glCompressedTexSubImage2D
	ogl->glBindTexture(GL_TEXTURE_3D, 0);
}

void Texture3D::LoadDataCompressed(void* buffer, uint64_t count)
{
	
}