#include "CameraControl.hpp"


CameraControl::CameraControl(CameraObject* camObj)
{
	cameraObject = camObj;
}


void CameraControl::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) lmbState = true; 
	if(event->button() == Qt::RightButton) rmbState = true; 
	if(event->button() == Qt::MiddleButton) mmbState = true; 
	
}

void CameraControl::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) lmbState = false; 
	if(event->button() == Qt::RightButton) rmbState = false;
	if(event->button() == Qt::MiddleButton) mmbState = false; 	
}

void CameraControl::mouseMoveEvent(QMouseEvent *event)
{
	
}

void CameraControl::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Shift) shiftState = true; 
}

void CameraControl::keyReleaseEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Shift) shiftState = false; 
}