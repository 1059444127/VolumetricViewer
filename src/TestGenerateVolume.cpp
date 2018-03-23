#include "TestGenerateVolume.hpp"


void TestGenerateVolume(void** buffer, uint64_t W, uint64_t H, uint64_t D)
{
	
	*buffer = new unsigned char[W * H * D * 4]; 
	
	for(uint64_t z = 0; z < D; z++)
	{
		for(uint64_t y = 0; y < H; y++)
		{
			for(uint64_t x = 0; x < W; x++)
			{
				((char*)*buffer)[(z * W * H + y * W + x) * 4 + 0] = (double)x / W * 255; 
				((char*)*buffer)[(z * W * H + y * W + x) * 4 + 1] = (double)y / H * 255; 
				((char*)*buffer)[(z * W * H + y * W + x) * 4 + 2] = (double)z / D * 255; 
				((char*)*buffer)[(z * W * H + y * W + x) * 4 + 3] = 255 * (sqrt(x * x + y * y + z * z) < (double)W / 2); 
			}
		}
	}
}