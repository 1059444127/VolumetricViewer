#include "CameraObject.hpp"


CameraObject::CameraObject()
{
	ortho = false; 
	nearClipping = 0.1f;
	farClipping = 10000.0f;
	fovV = 60.0f; 
}

glm::mat4 CameraObject::GetProjectionMatrix(float windowWidth, float windowHeight)
{
	float aspect = windowWidth / windowHeight; 
	
	glm::mat4 projMat; 
	if(!ortho) 
		projMat = glm::perspectiveLH(fovV, aspect, nearClipping, farClipping);
	else//have no idea if this is right yet ... TODO
		projMat = glm::ortho(-windowWidth/2, windowWidth/2, -windowHeight/2, windowHeight/2, nearClipping, farClipping);
	return projMat; 
}