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
	
		
	
		SampleMappingHistogram();
		QRectF boundingRect() const;
		int type() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


class SampleMappingCurve: public QGraphicsItem 
{
	public:
		enum { Type = UserType + 1 };
		
		SampleMappingCurve();
		QRectF boundingRect() const;
		int type() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


class SampleMappingAxis: public QGraphicsItem 
{
	public:
		enum { Type = UserType + 1 };
		
		int viewW;
		int viewH; 
		
		SampleMappingAxis();
		QRectF boundingRect() const;
		int type() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


class SampleMappingEditor: public QGraphicsView
{
	Q_OBJECT
	private:
		std::vector<SampleMappingNode*> nodes; 
		SampleMappingHistogram* histogram;
		SampleMappingCurve* curve;
		SampleMappingAxis* axis;
		
		QGraphicsScene* scene; 
		
	protected:
		void resizeEvent(QResizeEvent *event);
		
	public:
		SampleMappingEditor();

};