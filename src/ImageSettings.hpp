#pragma once

#include "Common.hpp"
#include "HelperWidgets.hpp"
#include "SampleMappingEditor.hpp"


class ImageSettings: public QWidget
{
	Q_OBJECT
	private:
		
		
	public:
		QGroupBox* groupBox; 
		QVBoxLayout* layoutGroup;
		QVBoxLayout* layoutBase;
		Vector3Chooser* chooserPosition;		
		Vector3Chooser* chooserRotation;
		Vector3Chooser* chooserScale;
		SampleMappingEditor* sampleMapping;
	
		ImageSettings();

};