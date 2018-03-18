#include "RenderViewport.hpp"


RenderViewport::RenderViewport()
{
}

void RenderViewport::initializeGL()
{
	QOpenGLFunctions* gl = QOpenGLContext::currentContext()->functions();
    gl->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void RenderViewport::resizeGL(int w, int h)
{
	
}

void RenderViewport::paintGL()
{
	QOpenGLFunctions* gl = QOpenGLContext::currentContext()->functions();
    gl->glClear(GL_COLOR_BUFFER_BIT);
	gl->glClear(GL_DEPTH_BUFFER_BIT);
	
	
}