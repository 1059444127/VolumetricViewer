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
		
	checkAxisVisible = new QCheckBox("Axis Visible");
	layoutBase->addWidget(checkAxisVisible);
	
	comboRenderer = new QComboBox();
	comboRenderer->addItem("Slice");
	comboRenderer->addItem("Ray");
	comboRenderer->addItem("Cinematic");
	layoutBase->addWidget(comboRenderer);
	
	imageSettings = new ImageSettings();
	layoutBase->addWidget(imageSettings);
}
