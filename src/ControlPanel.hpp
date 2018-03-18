#pragma once


#include "Common.hpp"
#include "HelperWidgets.hpp"

class ControlPanel: public QDockWidget
{
	Q_OBJECT
	public:
		QScrollArea* scrollAreaBase;
		QWidget* widgetBase; 
		QVBoxLayout* layoutBase;
		
		//Threshold
		QLabel* labelThreshold;
		
		ScalarChooser*  chooserIntensity;
		
	
		ControlPanel();
};