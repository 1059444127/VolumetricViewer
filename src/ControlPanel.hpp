#pragma once


#include "Common.hpp"
#include "HelperWidgets.hpp"
#include "ImageSettings.hpp"

class ControlPanel: public QDockWidget
{
	Q_OBJECT
	public:
		QScrollArea* scrollAreaBase;
		QWidget* widgetBase; 
		QVBoxLayout* layoutBase;
		
		QCheckBox* checkAxisVisible;
		
		ImageSettings* imageSettings;
	
		ControlPanel();
};