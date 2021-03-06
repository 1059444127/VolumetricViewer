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
	chooserScale = new Vector3Chooser("scale", 1, 1, 1);
	//layoutGroup->addWidget(chooserPosition); 
	//layoutGroup->addWidget(chooserRotation); 
	layoutGroup->addWidget(chooserScale);
	
	buttonSampleMapping = new QPushButton("Sample Mapping"); 
	layoutGroup->addWidget(buttonSampleMapping);
	
	sampleMapping = new SampleMappingEditor;
	
	connect(buttonSampleMapping, &QPushButton::clicked, [this]()
	{
		sampleMapping->show();
	});
	
}
