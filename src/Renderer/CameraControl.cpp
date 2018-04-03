#include "CameraControl.hpp"


CameraControl::CameraControl(CameraObject* camObj)
{
	cameraObject = camObj;
	zoom = 1;
	zoomSpeed = 0.06;
	roty = 0;
	rotx = 0; 
	rotySpeed = 0.2;
	rotxSpeed = 0.2;
	posX = 0;
	posY = 0;
	posZ = 0;
	moveSpeed = 0.01;
	firstMouseMove = true; 
}


void CameraControl::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) 
	{
		lmbState = true; 
		mousePrevX = event->globalX();
		mousePrevY = event->globalY();
		rotxPrev = rotx;
		rotyPrev = roty; 
	}
	if(event->button() == Qt::RightButton) rmbState = true; 
	if(event->button() == Qt::MiddleButton)
	{
		mmbState = true; 
		mousePrevX = event->globalX();
		mousePrevY = event->globalY();
		posXPrev = posX;
		posYPrev = posY;
		posZPrev = posZ;
	}
	
	if(event->button() == Qt::LeftButton || 
	   event->button() == Qt::RightButton || 
	   event->button() == Qt::MiddleButton)
		UpdateCamera();
}

void CameraControl::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{ 
		rotxPrev = rotx;
		rotyPrev = roty;
		lmbState = false; 
	}
	if(event->button() == Qt::RightButton) rmbState = false;
	if(event->button() == Qt::MiddleButton) mmbState = false; 	
	
	if(event->button() == Qt::LeftButton || 
	   event->button() == Qt::RightButton || 
	   event->button() == Qt::MiddleButton)
		UpdateCamera();
}

void CameraControl::wheelEvent(QWheelEvent *event)
{
	QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;

    if (!numPixels.isNull()) 
	{
        zoom += zoomSpeed * numPixels.y();
		if(zoom < 0.1) zoom = 0.1; 
		UpdateCamera();
		event->accept();
    } 
	else if (!numDegrees.isNull()) 
	{
        QPoint numSteps = numDegrees / 15;
        zoom += zoom * zoomSpeed * numSteps.y();
		if(zoom < 0.1) zoom = 0.1; 
		UpdateCamera();
		event->accept();
    }
	else
	{
		event->ignore(); 
	}
}

void CameraControl::mouseMoveEvent(QMouseEvent *event)
{
	if(lmbState)
	{		
		roty = rotySpeed * (event->globalX() - mousePrevX) + rotyPrev;
		rotx = rotxSpeed * (event->globalY() - mousePrevY) + rotxPrev;
		UpdateCamera(); 
	}
	else if(mmbState)
	{
		float degtorad = 0.0174532925;
		
		float deltaX = -moveSpeed * (event->globalX() - mousePrevX);
		float deltaY = moveSpeed * (event->globalY() - mousePrevY);
		
		glm::mat4 rotxM = glm::rotate(glm::mat4(1), degtorad * rotx, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotyM = glm::rotate(glm::mat4(1), degtorad * roty, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rotM = rotyM * rotxM; 	
		glm::vec4 deltaVec = rotM * glm::vec4(deltaX, deltaY, 0, 0);
		
		posX = posXPrev + deltaVec.x;
		posY = posYPrev + deltaVec.y;
		posZ = posZPrev + deltaVec.z;
		
		UpdateCamera(); 
	}
}

void CameraControl::keyPressEvent(QKeyEvent *event)
{
	
	if(event->key() == Qt::Key_Shift) shiftState = true; 
	
	if(event->key() == Qt::Key_F)
	{
		std::cout << "F!!!" << std::endl; 
		posX = 0;
		posY = 0;
		posZ = 0;
		UpdateCamera(); 
	}
}

void CameraControl::keyReleaseEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Shift) shiftState = false; 
}

void CameraControl::UpdateCamera()
{
	cameraObject->SetRotation(glm::vec3(rotx, roty, 0));
	
	float degtorad = 0.0174532925;
	float finalPosX = posX + zoom * -cos(degtorad * rotx)* sin(degtorad * roty);
	float finalPosY = posY + zoom * sin(degtorad * rotx);
	float finalPosZ = posZ + zoom * -cos(degtorad * rotx)* cos(degtorad * roty);
	cameraObject->SetPosition(glm::vec3(finalPosX, finalPosY, finalPosZ));
	
	std::cout << "Camera Updated:rot " << rotx << " " << roty
			  << " zoom " << zoom 
			  << " pos " << finalPosX << " " << finalPosY << " " << finalPosZ
			  << std::endl; 
	emit CameraUpdated();
}