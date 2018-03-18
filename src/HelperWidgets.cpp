#include "HelperWidgets.hpp"	
	
	
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
	
	slider->setMinimum(0);
	slider->setMaximum(100);
	slider->setPageStep(1);
	slider->setSingleStep(1);
	
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