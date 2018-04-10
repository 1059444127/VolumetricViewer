#pragma once

#include "Common.hpp"
#include "HelperWidgets.hpp"


class ImageSettings: public QWidget
{
	Q_OBJECT
	private:
		
		
	public:
		QVBoxLayout* layoutBase;
		Vector3Chooser* chooserPosition;		
		Vector3Chooser* chooserRotation;
		Vector3Chooser* chooserScale;
		QPushButton* deleteButton; 
	
		ImageSettings();

};