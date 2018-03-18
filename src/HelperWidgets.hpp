#pragma once

#include "Common.hpp"


class ScalarChooser: public QWidget
{
	Q_OBJECT
	private:
		double sliderStep; 
		double minVal;
		double maxVal; 
		QHBoxLayout* layout;
		QLabel* label;
		QSlider* slider;
		QDoubleSpinBox* spin;
		
	public:
		ScalarChooser(QString name, double minv=0, double maxv=1, double start=0);
		
	signals:
		void valueChanged(double val);
		
	public slots:
		void setValue(double val);
};