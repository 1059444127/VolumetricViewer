#pragma once

#include "Common.hpp"


class SampleMappingNode: public QGraphicsItem 
{
	public:
		enum { Type = UserType + 1 };
		
		QColor color; 
		
		SampleMappingNode();
		QRectF boundingRect() const;
		int type() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


class SampleMappingHistogram: public QGraphicsItem 
{
	public:
		enum { Type = UserType + 1 };
		
		QColor color; 
		
		SampleMappingHistogram();
		QRectF boundingRect() const;
		int type() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


class SampleMappingEditor: public QGraphicsView
{
	Q_OBJECT
	private:
		QGraphicsScene* scene; 
		
	public:
		SampleMappingEditor();

};