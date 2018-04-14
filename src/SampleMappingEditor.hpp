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
		
		bool selected; 
		
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
		enum { Type = UserType + 2 };
		
		int viewW;
		int viewH;
		
		std::vector<unsigned char> data; 
	
		SampleMappingHistogram();
		QRectF boundingRect() const;
		int type() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		void SetData(unsigned char* d, int len);
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
		
		enum { Type = UserType + 3 };
		
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
		enum { Type = UserType + 4 };
		
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
		QColor prevNodeColor; 
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
		void keyPressEvent(QKeyEvent * event);
		
	public:
		SampleMappingEditor();
		int GetViewW();
		int GetViewH();
		void Reset();
		void GetLUT(int bufferSize, float* textureBuffer);
		
	signals:
		void CurveChanged();
};