#pragma once


#include "Common.hpp"


class Image3D
{
	protected:
		uint64_t width;
		uint64_t height;
		uint64_t depth;
		uint64_t pixelSize;
		void* data;
		
	public:
		Image3D();
		Image3D(uint64_t W, uint64_t H, uint64_t D, uint64_t P);
		~Image3D();
		void Allocate(uint64_t W, uint64_t H, uint64_t D, uint64_t P);
		void Deallocate(); 
		void* Data();
	
};