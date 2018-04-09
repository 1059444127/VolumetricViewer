#pragma once

#include "Common.hpp"

class Vector3Chooser: public QWidget
{
	Q_OBJECT
	private:
		QHBoxLayout* layout;
		QLabel* label;
		QDoubleSpinBox* spinX;
		QDoubleSpinBox* spinY;
		QDoubleSpinBox* spinZ;
		double sx, sy, sz;
		
	public:
		Vector3Chooser(QString name, double defaultX=0, double defaultY=0, double defaultZ=0, 
					   double minX=-1000000, double minY=-1000000, double minZ=-1000000, 
					   double maxX=1000000, double maxY=1000000, double maxZ=1000000);
		
	signals:
		void valueChanged(double xV, double yV, double zV);
		
	public slots:
		void setValue(double xV, double yV, double zV);
};

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

