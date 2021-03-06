#include "Texture3D.hpp"


Texture3D::Texture3D()
{
	OPENGL_FUNC_MACRO
	
	ogl->glGenTextures(1, &textureId);
	
	ogl->glBindTexture(GL_TEXTURE_3D, textureId);
	
	ogl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	ogl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	ogl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	ogl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	ogl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	float bcolor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ogl->glTexParameterfv(GL_TEXTURE_3D, GL_TEXTURE_BORDER_COLOR, bcolor);
	
	ogl->glBindTexture(GL_TEXTURE_3D, 0);
	
	width = 0;
	height = 0;
	depth = 0; 
}

void Texture3D::Allocate(uint64_t w, uint64_t h, uint64_t d, bool compressed)
{
	width = w;
	height = h;
	depth = d; 
	
	OPENGL_FUNC_MACRO

	ogl->glBindTexture(GL_TEXTURE_3D, textureId);
	
	if(compressed)
	{
		ogl->glTexImage3D(GL_TEXTURE_3D, 0, GL_COMPRESSED_RGBA, width, height, depth,
						  0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}
	else
	{
		ogl->glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, width, height, depth,
						  0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}
	ogl->glBindTexture(GL_TEXTURE_3D, 0);
}

void Texture3D::Destroy()
{
	OPENGL_FUNC_MACRO

	ogl->glDeleteTextures(1, &textureId);
}

void Texture3D::LoadData(void* buffer)
{
	OPENGL_FUNC_MACRO

	ogl->glBindTexture(GL_TEXTURE_3D, textureId);
	ogl->glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, width, height, depth, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	ogl->glBindTexture(GL_TEXTURE_3D, 0);
}

void Texture3D::LoadDataSlice(void* buffer, uint64_t Z)
{
	OPENGL_FUNC_MACRO

	ogl->glBindTexture(GL_TEXTURE_3D, textureId);
	ogl->glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, Z, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	ogl->glBindTexture(GL_TEXTURE_3D, 0);
}

unsigned int Texture3D::GetTextureId()
{
	return textureId; 
}

uint64_t Texture3D::Width()
{
	return width; 
}

uint64_t Texture3D::Height()
{
	return height;
}

uint64_t Texture3D::Depth()
{
	return depth; 
}
