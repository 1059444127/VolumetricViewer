#pragma once


#include "Common.hpp"


class RenderViewport: public QOpenGLWidget
{
	Q_OBJECT
	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int w, int h);
		
	public:
		RenderViewport();
		
};