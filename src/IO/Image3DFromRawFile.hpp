#pragma once

#include "../Common.hpp"
#include "../Image3D.hpp"

bool Image3DFromRawFileSequence(Image3D* image, std::vector<std::string> fileNames);
bool Image3DFromRawFile(Image3D* image, std::string fileNames);