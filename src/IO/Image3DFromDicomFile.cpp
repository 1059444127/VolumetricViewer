#include "Image3DFromDicomFile.hpp"


#include <dcmtk/dcmimage/diregist.h>
#include <dcmtk/dcmimgle/dcmimage.h>


bool Image3DFromDicomFile(Image3D* image, const char* fileName)
{
	DicomImage *img = new DicomImage(fileName);
	if(img != NULL)
	{
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
			
				return true; 
			}
		} 
		else
		{
			std::cerr << "Image3DFromDicomFile: cannot load DICOM image (" << DicomImage::getString(img->getStatus()) << ")" << std::endl;
		}
	}
	delete image;
	return false; 
}
