#include "ImageSettings.hpp"


ImageSettings::ImageSettings()
{
	groupBox = new QGroupBox("Image Settings");
	layoutBase = new QVBoxLayout();
	layoutBase->setMargin(2);
	setLayout(layoutBase);
	layoutBase->addWidget(groupBox);
	
	layoutGroup = new QVBoxLayout();
	layoutGroup->setMargin(2);
	groupBox->setLayout(layoutGroup);
	
	chooserPosition = new Vector3Chooser("position");		
	chooserRotation = new Vector3Chooser("rotation");
	chooserScale = new Vector3Chooser("scale");
	//layoutGroup->addWidget(chooserPosition); 
	//layoutGroup->addWidget(chooserRotation); 
	layoutGroup->addWidget(chooserScale);
	
	sampleMapping = new SampleMappingEditor;
	layoutGroup->addWidget(sampleMapping);
}
