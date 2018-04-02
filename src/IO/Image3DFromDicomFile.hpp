#pragma once

#include "../Common.hpp"
#include "../Image3D.hpp"

bool Image3DFromDicomFile(Image3D* image, std::string fileName);
bool Image3DFromDicomFileSequence(Image3D* image, std::vector<std::string> fileNames);