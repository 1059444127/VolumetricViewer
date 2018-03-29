#include "TestGenerateVolume.hpp"


void TestGenerateVolume(void** buffer, uint64_t W, uint64_t H, uint64_t D)
{
	
	*buffer = new unsigned char[W * H * D * 4]; 
	
	double cX = (double)W / 2;
	double cY = (double)H / 2;
	double cZ = (double)D / 2;
	
	for(uint64_t z = 0; z < D; z++)
	{
		for(uint64_t y = 0; y < H; y++)
		{
			for(uint64_t x = 0; x < W; x++)
			{
				double dx = x - cX;
				double dy = y - cY;
				double dz = z - cZ;
			
				((char*)*buffer)[(z * W * H + y * W + x) * 4 + 0] = (double)x / W * 255; 
				((char*)*buffer)[(z * W * H + y * W + x) * 4 + 1] = (double)y / H * 255; 
				((char*)*buffer)[(z * W * H + y * W + x) * 4 + 2] = (double)z / D * 255; 
				((char*)*buffer)[(z * W * H + y * W + x) * 4 + 3] = 32 * (sqrt(dx * dx + dy * dy + dz * dz) < (double)W / 2); 
			}
		}
	}
}