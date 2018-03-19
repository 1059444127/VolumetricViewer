#pragma once


#include "../Common.hpp"


class Object3D
{
	private:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		
	public:
		Object3D();
		virtual void Init(){}
		virtual void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix){}
		glm::mat4 GetModelTransform(); 
		glm::vec3 GetPosition();
		void SetPosition(glm::vec3 pos);
		glm::vec3 GetRotation();
		void SetRotation(glm::vec3 rot);
		glm::vec3 GetScale();
		void SetScale(glm::vec3 sca);
};