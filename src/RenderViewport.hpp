#pragma once


#include "Common.hpp"

#include "Renderer/CameraObject.hpp"
#include "Renderer/TextureVolumeObject.hpp"
#include "Renderer/Texture3D.hpp"


class RenderViewport: public QOpenGLWidget
{
	Q_OBJECT
	protected:
		int windowWidth;
		int windowHeight; 
	
		CameraObject* cameraObject; 
		TextureVolumeObject* textureVolumeObject; 
		Texture3D* textureVolume; 
	
		void initializeGL();
		void paintGL();
		void resizeGL(int w, int h);
		
	public:
		RenderViewport();
		
};