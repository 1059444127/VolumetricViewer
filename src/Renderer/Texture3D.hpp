#pragma once


#include "../Common.hpp"


class Texture3D
{
	public:
		unsigned int textureId; 
		uint64_t width;
		uint64_t height; 
		uint64_t depth; 
		void* buffer;
		
		Texture3D();
		void Allocate(uint64_t w, uint64_t h, uint64_t d);
		void AllocateCompressed(uint64_t w, uint64_t h, uint64_t d);
		void LoadData(void* buffer, uint64_t count);
		void LoadDataCompressed(void* buffer, uint64_t count);
};