#pragma once


#include "Common.hpp"

#include "CameraObject.hpp"


class CameraControl
{
	protected:
		bool lmbState;
		bool rmbState; 
		bool mmbState; 
		bool shiftState;
		CameraObject* cameraObject; 
		
	public:
		CameraControl(CameraObject* camObj);
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
};