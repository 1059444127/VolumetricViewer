#include "SampleMappingEditor.hpp"


//
//SampleMappingNode
//


SampleMappingNode::SampleMappingNode()
{
}

QRectF SampleMappingNode::boundingRect() const
{
	qreal penWidth = 1;
	return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
				  20 + penWidth, 20 + penWidth);
}

int SampleMappingNode::type() const
{
	return Type;
}

void SampleMappingNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(QPen(color));
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
	qreal penWidth = 1;
	return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
				  20 + penWidth, 20 + penWidth);
}

int SampleMappingHistogram::type() const
{
	return Type;
}

void SampleMappingHistogram::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	
}


//
//SampleMappingEditor
//


SampleMappingEditor::SampleMappingEditor()
{
	scene = new QGraphicsScene(this);
	setScene(scene);
	
	setInteractive(true); 
}