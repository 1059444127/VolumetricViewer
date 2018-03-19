#pragma once


#include "Object3D.hpp"


class CameraObject: public Object3D
{
	private:
		bool ortho;
		float nearClipping;
		float farClipping;
		float fovV;		
	
	public:
		CameraObject();
		glm::mat4 GetProjectionMatrix(float windowWidth, float windowHeight);
};