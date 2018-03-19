#pragma once


#include "Object3D.hpp"

class TextureVolumeObject: public Object3D
{
	public:
		TextureVolumeObject();
		virtual void Init();
		virtual void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
};