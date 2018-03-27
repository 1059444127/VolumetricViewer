#pragma once


#include "Common.hpp"

#include "CameraObject.hpp"


class CameraControl: public QObject 
{
	Q_OBJECT
	
	protected:
		bool lmbState;
		bool rmbState; 
		bool mmbState; 
		bool shiftState;
		bool firstMouseMove; 
		int mousePrevX;
		int mousePrevY;
		float zoomSpeed; 
		float zoom; 
		float rotySpeed;
		float roty;
		float rotxSpeed; 
		float rotx;
		float rotyPrev;
		float rotxPrev;
		float moveSpeed; 
		float posX;
		float posY;
		float posZ;
		float posXPrev;
		float posYPrev;
		float posZPrev;
		CameraObject* cameraObject; 
		
	signals:
		void CameraUpdated();
		
	public:
		CameraControl(CameraObject* camObj);
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void wheelEvent(QWheelEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
		void UpdateCamera(); 
};