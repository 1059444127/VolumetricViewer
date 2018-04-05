#include "Image3DFromTIFFFileSequence.hpp"



bool Image3DFromTIFFFileSequence(Image3D* image, std::vector<std::string> fileNames)
{
	//Check for all same size in stack
	uint32_t width, height; 
	bool firstRun = true; 
	for(int i = 0; i < fileNames.size(); i++)
	{
		TIFF* tif = TIFFOpen(fileNames[i].c_str(), "r");
		
		if (tif) 
		{
			uint32_t w, h;
			TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
			TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
			if(firstRun)
			{
				width = w;
				height = h;
			}
			else
			{
				if(w != width || h != height)	
				{
					std::cerr << "Image3DFromTIFFFileSequence: Images not the same size" << fileNames[i] << std::endl;
					return false; 
				}
			}
			TIFFClose(tif);
		}
	}
	
	//Check if images have some wifdth and height
	if(width <= 0 || height <= 0)
	{
		std::cerr << "Image3DFromTIFFFileSequence: Images have zero size" << fileNames[i] << std::endl;
		return false;
	}
	
	//Allocate Image
	image->Allocate(width, height, fileNames.size(), 4);
	
	//Load Data
	for(int i = 0; i < fileNames.size(); i++)
	{
		TIFF* tif = TIFFOpen(fileNames[i].c_str(), "r");
		
		if (tif) 
		{
			unsigned char* imageData = (unsigned char*)image->Data() + width * height * 4 * i;
			TIFFReadRGBAImage(tif, w, h, imageData, 0);
			TIFFClose(tif);
		}
	}
	
	return true; 
}