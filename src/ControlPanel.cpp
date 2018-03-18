#include "ControlPanel.hpp"


ControlPanel::ControlPanel(): QDockWidget("Control Panel")
{
	setMinimumWidth(300);
	
	scrollAreaBase = new QScrollArea();
	widgetBase = new QWidget();
	layoutBase = new QVBoxLayout();
	
	widgetBase->setLayout(layoutBase);
	scrollAreaBase->setWidget(widgetBase);
	scrollAreaBase->setWidgetResizable(true);
	setWidget(scrollAreaBase);
	
	layoutBase->setAlignment(Qt::AlignTop);
		
	//Threshold
	chooserIntensity = new ScalarChooser("Intensity");
	layoutBase->addWidget(chooserIntensity); 
	
}
