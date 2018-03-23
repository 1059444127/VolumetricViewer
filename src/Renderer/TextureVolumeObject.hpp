#pragma once


#include "Object3D.hpp"
#include "Texture3D.hpp"


class TextureVolumeObject: public Object3D
{
	protected:
		struct Vertex
		{
			float x;
			float y;
			float z;
			float w;
		};
		
		struct Triangle
		{
			uint32_t v0;
			uint32_t v1;
			uint32_t v2;
		};
		
		static std::string vertSrc;
		static std::string fragSrc; 
		static int programShaderObject;
		static int vertexShaderObject;
		static int fragmentShaderObject;
		
		Texture3D* volumeTexture; 
		
		unsigned int volumeSlices;
		
		unsigned int vertexBuffer;
		unsigned int elementBuffer;
		unsigned int vertexArrayObject;
		
		float brightness;
		float contrast;
	
	public:
		static void InitSystem();
		
		TextureVolumeObject(unsigned int slices=512);
		virtual void Init();
		virtual void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
		virtual void Destroy();
		
		void SetVolumeTexture(Texture3D* vt);
};