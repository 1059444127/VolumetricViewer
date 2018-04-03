#include "RenderViewport.hpp"


#include "Util.hpp"

#include "TestGenerateVolume.hpp"

#include "IO/Image3DFromDicomFile.hpp"


RenderViewport::RenderViewport()
{
	setFocusPolicy(Qt::ClickFocus);
}

void RenderViewport::initializeGL()
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();
    ogl->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	cameraObject = new CameraObject;
	cameraControl = new CameraControl(cameraObject);
	
	connect(cameraControl, &CameraControl::CameraUpdated, [this](){update(); });
	
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

void RenderViewport::mousePressEvent(QMouseEvent *event)
{
	cameraControl->mousePressEvent(event);
}

void RenderViewport::mouseReleaseEvent(QMouseEvent *event)
{
	cameraControl->mouseReleaseEvent(event);
}

void RenderViewport::mouseMoveEvent(QMouseEvent *event)
{
	cameraControl->mouseMoveEvent(event); 
}

void RenderViewport::wheelEvent(QWheelEvent *event)
{
	cameraControl->wheelEvent(event); 
}

void RenderViewport::keyPressEvent(QKeyEvent *event)
{
	cameraControl->keyPressEvent(event);
}

void RenderViewport::keyReleaseEvent(QKeyEvent *event)
{
	cameraControl->keyReleaseEvent(event); 
}

void RenderViewport::ImportDicomFile(QString fileName)
{
	
}

void RenderViewport::ImportDicomFileSequence(QStringList fileNames)
{
	std::vector<std::string> files;
	for(int i = 0; i < fileNames.size(); i++)
		files.push_back(fileNames.at(i).toStdString());
	Image3D image3D;
	bool loadGood = Image3DFromDicomFileSequence(&image3D, files);
	if(!loadGood)
		return; 
	textureVolume->LoadData(image3D.Data(), image3D.Width() * image3D.Height() * image3D.Depth());
	
}