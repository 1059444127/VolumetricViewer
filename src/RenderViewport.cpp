#include "RenderViewport.hpp"


#include "Util.hpp"

#include "TestGenerateVolume.hpp"


RenderViewport::RenderViewport()
{
}

void RenderViewport::initializeGL()
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();
    ogl->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	cameraObject = new CameraObject;
	textureVolumeObject = new TextureVolumeObject;
	TextureVolumeObject::InitSystem(); 
	textureVolumeObject->Init();
	
	textureVolume = new Texture3D; 
	
	textureVolume->Allocate(512, 512, 512);
	void* data; 
	TestGenerateVolume(&data, 512, 512, 512);
	textureVolume->LoadData(data, 512 * 512 * 512);
	
	textureVolumeObject->SetVolumeTexture(textureVolume); 
}

void RenderViewport::resizeGL(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
}

void RenderViewport::paintGL()
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();
    ogl->glClear(GL_COLOR_BUFFER_BIT);
	ogl->glClear(GL_DEPTH_BUFFER_BIT);
	
	textureVolumeObject->Render(cameraObject->GetViewMatrix(), cameraObject->GetProjectionMatrix(windowWidth, windowHeight));
	
	PrintGLErrors();
}