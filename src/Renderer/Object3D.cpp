#include "Object3D.hpp"


Object3D::Object3D()
{
	position = glm::vec3(0, 0, 0); 
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	visible = true; 
}

glm::mat4 Object3D::GetModelMatrix()
{
	float degtorad = 0.01745329251;
	glm::mat4 translateM = glm::translate(glm::mat4(1), position);
	glm::mat4 scaleM = glm::scale(glm::mat4(1), scale);
	glm::mat4 rotxM = glm::rotate(glm::mat4(1), degtorad * rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotyM = glm::rotate(glm::mat4(1), degtorad * rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotzM = glm::rotate(glm::mat4(1), degtorad * rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotM = rotyM * rotxM * rotzM; 		
	return translateM * rotM * scaleM;
}
	
glm::vec3 Object3D::GetPosition()
{
	return position;
}

void Object3D::SetPosition(glm::vec3 pos)
{
	position = pos; 
}

glm::vec3 Object3D::GetRotation()
{
	return rotation; 
}

void Object3D::SetRotation(glm::vec3 rot)
{
	rotation = rot; 
}

glm::vec3 Object3D::GetScale()
{
	return scale; 
}

void Object3D::SetScale(glm::vec3 sca)
{
	scale = sca; 
}

bool Object3D::GetVisible()
{
	return visible; 
}

void Object3D::SetVisible(bool v)
{
	visible = v;
}
