#pragma once

#include "Common.hpp"
#include "HelperWidgets.hpp"


class ImageSettings: public QWidget
{
	Q_OBJECT
	private:
		
		
	public:
		QCheckBox* checkAxisVisible;
		Vector3Chooser* chooserPosition;		
		Vector3Chooser* chooserRotation;
		Vector3Chooser* chooserScale;
	
	
		ImageSettings();

};