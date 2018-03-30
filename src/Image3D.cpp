#include "Image3D.hpp"

Image3D::Image3D()
{
	width = 0;
	height = 0; 
	depth = 0;
	pixelSize = 0;
}

Image3D::Image3D(uint64_t W, uint64_t H, uint64_t D, uint64_t P)
{
	Allocate(W, H, D, P);
}

Image3D::~Image3D()
{
	Deallocate();
}

void Image3D::Allocate(uint64_t W, uint64_t H, uint64_t D, uint64_t P)
{
	width = W;
	height = H; 
	depth = D;
	pixelSize = P; 
	data = new unsigned char[W * H * D * P];
}

void Image3D::Deallocate()
{
	if(width > 0 && height > 0 && depth > 0 && pixelSize > 0)
		delete[] (unsigned char*)data; 
}

void* Image3D::Data()
{
	return data; 
}
