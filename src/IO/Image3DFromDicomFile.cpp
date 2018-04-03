#include "Image3DFromDicomFile.hpp"


#include <dcmtk/dcmimage/diregist.h>
#include <dcmtk/dcmimgle/dcmimage.h>


bool Image3DFromDicomFile(Image3D* image, std::string fileName)
{
	DicomImage *img = new DicomImage(fileName.c_str());
	
	if(img == NULL)
		return false; 
	
	if(img->getStatus() == EIS_Normal)
	{
		//Get info from Dicom Image
		uint64_t W = img->getWidth();
		uint64_t H = img->getHeight();
		uint64_t D = img->getNumberOfFrames();
		uint64_t bitsPerSample = img->getDepth();
		std::cout << "Dicom Image Info:width" << W << " height" << H << " depth:" << D << " bitsPerSample:" << bitsPerSample << std::endl;  
		
		//Get image data from dicom image
		image->Allocate(W, H, D, bitsPerSample);
		Uint8 *pixelData = (Uint8 *)(img->getOutputData(8 /* bits per sample */));
		if (pixelData != NULL)
		{
			
		}
	}
	else
	{
		std::cerr << "Image3DFromDicomFile: cannot load DICOM image (" << DicomImage::getString(img->getStatus()) << ")" << std::endl;
		return false; 
	}
	
	return true;
}

bool Image3DFromDicomFileSequence(Image3D* image, std::vector<std::string> fileNames)
{
	if(fileNames.size() == 0)
		return false; 
	//Doo check to see if all slices are same width and height and have some frame data
	std::cout << "Image3DFromDicomFileSequence: checking sequence for uniformality" << std::endl; 
	bool firstPass = true; 
	uint64_t width;
	uint64_t height; 
	for(int i = 0; i < fileNames.size(); i++)
	{
		if(firstPass)
		{
			DicomImage* img = new DicomImage(fileNames[i].c_str());
			uint64_t W = img->getWidth();
			uint64_t H = img->getHeight();
			uint64_t D = img->getNumberOfFrames();
			delete img;
			
			if(D < 1) return false; 
			
			width = W;
			height = H;
			
			if(width == 0 || height == 0) return false; 
			
			firstPass = false; 	
		}
		else
		{
			DicomImage* img = new DicomImage(fileNames[i].c_str());
			uint64_t W = img->getWidth();
			uint64_t H = img->getHeight();
			uint64_t D = img->getNumberOfFrames();
			delete img;
			
			if(D < 1) return false; 
			
			if(W != width) return false;
			if(H != height) return false; 
		}
		
	}
	
	image->Allocate(width, height, fileNames.size(), 4);
	std::cout << "Image3DFromDicomFileSequence: copying image data to 3d image" << std::endl; 
	//Load each frame 
	for(int i = 0; i < fileNames.size(); i++)
	{
		DicomImage* img = new DicomImage(fileNames[i].c_str());
		
		unsigned char* imageData = (unsigned char*)image->Data() + width * height * i; 
		
		img->getOutputData(imageData, width * height * 4, 32); 
		
		delete img;
	}
	
	return true; 
}