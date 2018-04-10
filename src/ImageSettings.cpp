#include "ImageSettings.hpp"


ImageSettings::ImageSettings()
{
	layoutBase = new QVBoxLayout();
	setLayout(layoutBase);
	chooserPosition = new Vector3Chooser("position");		
	chooserRotation = new Vector3Chooser("rotation");
	chooserScale = new Vector3Chooser("scale");
	layoutBase->addWidget(chooserPosition); 
	layoutBase->addWidget(chooserRotation); 
	layoutBase->addWidget(chooserScale);
	
	deleteButton = new QPushButton("Delete"); 
	layoutBase->addWidget(deleteButton);
}
