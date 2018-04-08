#include "HelperWidgets.hpp"	
	
	
Vector3Chooser::Vector3Chooser(QString name, double defaultX, double defaultY, double defaultZ, 
					   double minX, double minY, double minZ, 
					   double maxX, double maxY, double maxZ)
{
	layout = new QHBoxLayout();
	setLayout(layout); 
	
	label = new QLabel(name);
	spinX = new QDoubleSpinBox();
	spinY = new QDoubleSpinBox();
	spinZ = new QDoubleSpinBox();
	
	layout->addWidget(label);
	layout->addWidget(spinX);
	layout->addWidget(spinY);
	layout->addWidget(spinZ);
	
	sx = defaultX;
	sy = defaultY;
	sz = defaultZ;
	
	spinX->setValue(sx);
	spinY->setValue(sy);
	spinZ->setValue(sz);
	
	spinX->setSingleStep(0.1);
	spinY->setSingleStep(0.1);
	spinZ->setSingleStep(0.1);
	
	connect(spinX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=, this](double v)
	{
		sx = v;
		emit valueChanged(sx, sy, sz);
	});
	
	connect(spinY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=, this](double v)
	{
		sy = v;
		emit valueChanged(sx, sy, sz);
	});
	
	connect(spinZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=, this](double v)
	{
		sz = v;
		emit valueChanged(sx, sy, sz);
	});
}

void Vector3Chooser::setValue(double xV, double yV, double zV)
{
	spinX->setValue(xV);
	spinY->setValue(yV);
	spinZ->setValue(zV);
}

	
ScalarChooser::ScalarChooser(QString name, double minv, double maxv, double start)
{
	minVal = minv;
	maxVal = maxv;
	
	layout = new QHBoxLayout();
	setLayout(layout); 
	
	label = new QLabel(name);
	slider = new QSlider(Qt::Horizontal);
	spin = new QDoubleSpinBox();
	
	
	layout->addWidget(label);
	layout->addWidget(slider);
	layout->addWidget(spin);
	
	sliderStep = (maxv - minv) / 100.0;
	
	spin->setMaximum(maxv);
	spin->setMinimum(minv);
	spin->setSingleStep(sliderStep);
	spin->setValue(start);
	
	slider->setMinimum(0);
	slider->setMaximum(100);
	slider->setPageStep(1);
	slider->setSingleStep(1);
	slider->setValue((start - minv) / sliderStep);
	
	connect(slider, &QSlider::valueChanged, [=, this](int v)
	{
		double newVal = minv + v * sliderStep;
		spin->setValue(newVal);
		emit valueChanged(newVal);
	});
	
	
	connect(spin,  QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=, this](double v)
	{
		slider->setValue((v - minv) / sliderStep); 
		emit valueChanged(v);
	});
}

void ScalarChooser::setValue(double val)
{
	spin->setValue(minVal + val * sliderStep);
	//slider->setValue((val - minVal) / sliderStep); 
}