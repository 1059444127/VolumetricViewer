#include "SampleMappingEditor.hpp"


//
//SampleMappingNode
//


SampleMappingNode::SampleMappingNode()
{
	color = QColor(255, 255, 0);
}

QRectF SampleMappingNode::boundingRect() const
{
	return QRectF(-10, -10, 20, 20);
}

int SampleMappingNode::type() const
{
	return Type;
}

void SampleMappingNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QColor colorBorder = QColor(255, 255, 255);
	painter->setPen(QPen(colorBorder));
	
	painter->drawEllipse(-4, -4, 8, 8);
	
	painter->setBrush(QBrush(color, Qt::SolidPattern));
	
	painter->drawEllipse(-4, -4, 8, 8);
	
}


//
//SampleMappingHistogram
//


SampleMappingHistogram::SampleMappingHistogram()
{
}

QRectF SampleMappingHistogram::boundingRect() const
{
	return QRectF(-10, -10, 20, 20);
}

int SampleMappingHistogram::type() const
{
	return Type;
}

void SampleMappingHistogram::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	
}


//
//SampleMappingCurve
//


SampleMappingCurve::SampleMappingCurve()
{
	
}

QRectF SampleMappingCurve::boundingRect() const
{
	return QRectF(-10, -10, 20, 20);
}

int SampleMappingCurve::type() const
{
	return Type;
}

void SampleMappingCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	
}


//
//SampleMappingAxis
//

		
SampleMappingAxis::SampleMappingAxis()
{
	
}

QRectF SampleMappingAxis::boundingRect() const
{
	return QRectF(-10, -10, 20, 20);
}

int SampleMappingAxis::type() const
{
	return Type;
}

void SampleMappingAxis::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->drawLine(0, 0, 100, 0);
}


//
//SampleMappingEditor
//


SampleMappingEditor::SampleMappingEditor()
{
	scene = new QGraphicsScene(this);
	
	setScene(scene);
	
	setInteractive(true); 
	
	histogram = new SampleMappingHistogram;
	scene->addItem(histogram);
	
	curve = new SampleMappingCurve;
	scene->addItem(curve);
	
	axis = new SampleMappingAxis;
	scene->addItem(axis);
	
	
	int viewportW = viewport()->geometry().width();
	int viewportH = viewport()->geometry().width();
	setSceneRect(0, 0, viewportW, viewportH * 3/4);
	
}