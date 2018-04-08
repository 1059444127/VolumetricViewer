#pragma once


#include "Object3D.hpp"
#include "Texture3D.hpp"


class AxisObject: public Object3D
{
	protected:
		struct Vertex
		{
			float x;
			float y;
			float z;
			float w;
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a;
		};
		
		static std::string vertSrc;
		static std::string fragSrc; 
		static int programShaderObject;
		static int vertexShaderObject;
		static int fragmentShaderObject;
						
		unsigned int vertexBuffer;
		unsigned int elementBuffer;
		unsigned int vertexArrayObject;
			
	public:
		static void InitSystem();
		
		AxisObject();
		virtual void Init();
		virtual void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
		virtual void Destroy();
		
		void SetVolumeTexture(Texture3D* vt);
};