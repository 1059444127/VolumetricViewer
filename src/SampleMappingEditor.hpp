#pragma once

#include "Common.hpp"


//
//SampleMappingNode
//


class SampleMappingNode: public QGraphicsItem 
{
	public:
		enum { Type = UserType + 1 };
		
		int viewW;
		int viewH;
		
		double xPos, yPos;
		
		QColor color; 
		
		SampleMappingNode(double x, double y);
		QRectF boundingRect() const;
		int type() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


//
//SampleMappingHistogram
//


class SampleMappingHistogram: public QGraphicsItem 
{
	public:
		enum { Type = UserType + 1 };
		
		int viewW;
		int viewH;
		
		std::vector<char> data; 
	
		SampleMappingHistogram();
		QRectF boundingRect() const;
		int type() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		void SetData(char* d, int len);
};


//
//SampleMappingCurve
//


class SampleMappingCurve: public QGraphicsItem 
{
	public:
	
		int viewW;
		int viewH;
		
		std::vector<SampleMappingNode*>* nodes; 
		
		enum { Type = UserType + 1 };
		
		SampleMappingCurve();
		QRectF boundingRect() const;
		int type() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


//
//SampleMappingAxis
//


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


//
//SampleMappingEditor
//


class SampleMappingEditor: public QGraphicsView
{
	Q_OBJECT
	private:
		SampleMappingNode* selectedNode; 
		std::vector<SampleMappingNode*> nodes; 
		SampleMappingHistogram* histogram;
		SampleMappingCurve* curve;
		SampleMappingAxis* axis;
		
		QGraphicsScene* scene; 
		
	protected:
		void resizeEvent(QResizeEvent *event);
		void mouseDoubleClickEvent(QMouseEvent * event);
		void mousePressEvent(QMouseEvent * event);
		void mouseMoveEvent(QMouseEvent * event);
		
	public:
		SampleMappingEditor();
		int GetViewW();
		int GetViewH();
		

};