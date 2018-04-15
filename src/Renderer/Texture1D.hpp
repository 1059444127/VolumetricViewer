#pragma once


#include "../Common.hpp"


class Texture1D
{
	protected:
		unsigned int textureId; 
		uint64_t width;
		
	public:
		Texture1D();
		void Allocate(uint64_t w);
		void Destroy();
		void LoadData(void* buffer);
		unsigned int GetTextureId();
		uint64_t Width();
};