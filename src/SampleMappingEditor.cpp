#include "SampleMappingEditor.hpp"


//
//SampleMappingNode
//


SampleMappingNode::SampleMappingNode(double x, double y)
{
	setZValue(3);
	xPos = x;
	yPos = y; 
	color = QColor(255, 255, 0);
}

QRectF SampleMappingNode::boundingRect() const
{
	return QRectF(-5, -5, 10, 10);
}

int SampleMappingNode::type() const
{
	return Type;
}

void SampleMappingNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QColor colorBorder = QColor(255, 255, 255);
	painter->setPen(QPen(colorBorder));
	
	int sceneX = xPos * viewW;
	int sceneY = yPos * viewH;
	painter->drawEllipse(sceneX - 5, -sceneY - 5, 10, 10);
	
	painter->setBrush(QBrush(color, Qt::SolidPattern));
	
	sceneX = xPos * viewW;
	sceneY = yPos * viewH;
	painter->drawEllipse(sceneX - 5, -sceneY - 5, 10, 10);
	
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
	return QRectF(-1000, -1000, 20000, 20000);
}

int SampleMappingCurve::type() const
{
	return Type;
}

void SampleMappingCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPainterPath path;
	
	if(nodes->size() > 0 )
	{
		std::vector<QPointF> points; 
		for(int i = 0; i < nodes->size(); i++)
		{
			double x = (*nodes)[i]->xPos * viewW;
			double y = -(*nodes)[i]->yPos * viewH;
			points.push_back(QPointF(x, y));
		}
		
		sort( points.begin( ), points.end( ), [ ]( const QPointF& lhs, const QPointF& rhs )
		{
		   return lhs.x() < rhs.x();
		});
		
		
		for(int i = 0; i < points.size(); i++)
		{
			double x = points[i].x();
			double y = points[i].y();
			
			if(i == 0)
				path.moveTo(QPointF(x, y));
			else
				path.cubicTo(QPointF(x, y), QPointF(x, y), QPointF(x, y));
		}
	}
	
	QColor colorBorder = QColor(255, 255, 255);
	painter->setPen(QPen(colorBorder));
	painter->strokePath(path, painter->pen());
}


//
//SampleMappingAxis
//

		
SampleMappingAxis::SampleMappingAxis()
{
	setZValue(0);
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
	painter->drawLine(0, 0, 0, -100000);
	painter->drawLine(0, 0, 100000, 0);
	
	QFont font = painter->font() ;

	font.setPointSize(8);

	painter->setFont(font);
	
	
	for(int i = 0; i < 11; i++)
	{
		int x = i * viewW/10;
		painter->setPen(QColor(255, 255, 255, 30));
		painter->drawLine(x, 10, x, -viewH);
		std::stringstream ss;
		ss << (double)i/10.0; 
		painter->setPen(QColor(255, 255, 255, 128));
		painter->drawText(x, 24, ss.str().c_str());
	}
	
	for(int i = 0; i < 11; i++)
	{
		int y = i * viewH/10;
		painter->setPen(QColor(255, 255, 255, 30));
		painter->drawLine(-10, -y, viewW, -y);
		std::stringstream ss;
		ss << (double)i / 10.0; 
		painter->setPen(QColor(255, 255, 255, 128));
		painter->drawText(-28, -y, ss.str().c_str());
	}
	
	painter->setPen(QColor(255, 255, 255, 20));
	painter->drawLine(0, 0, viewW, -viewH);
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
	curve->nodes = &nodes; 
	scene->addItem(curve);
	
	axis = new SampleMappingAxis;
	scene->addItem(axis);
	
	
	int viewportW = viewport()->geometry().width();
	int viewportH = viewport()->geometry().height();
	setSceneRect(-20, -viewportH + 20, viewportW, viewportH);
	setTransformationAnchor(QGraphicsView::NoAnchor); 
	
	axis->viewW = GetViewW();
	axis->viewH = GetViewH();
}

void SampleMappingEditor::resizeEvent(QResizeEvent *event)
{
	int viewportW = viewport()->geometry().width();
	int viewportH = viewport()->geometry().height();
	setSceneRect(-40, -viewportH + 40, viewportW, viewportH);
	
	axis->viewW = GetViewW();
	axis->viewH = GetViewH();
	
	curve->viewW = GetViewW();
	curve->viewH = GetViewH();
	
	for(int i = 0; i < nodes.size(); i++)
	{
		nodes[i]->viewW = GetViewW();
		nodes[i]->viewH = GetViewH();
	}
	
}

void SampleMappingEditor::mouseDoubleClickEvent(QMouseEvent * event)
{
	int mouseX = event->x();
	int mouseY = event->y();
	QPointF pointInScene = mapToScene(QPoint(mouseX, mouseY));
	double x = pointInScene.x() / GetViewW();
	double y = -pointInScene.y() / GetViewH();
	SampleMappingNode* newNode = new SampleMappingNode(x, y);
	newNode->viewW = GetViewW();
	newNode->viewH = GetViewH();
	nodes.push_back(newNode);
	scene->addItem(newNode);
	
	scene->update(); 
	update(); 
	
	std::cout << "Added New Node at " << x << ", " << y << std::endl; 
}

void SampleMappingEditor::mousePressEvent(QMouseEvent * event)
{
	
}

void SampleMappingEditor::mouseMoveEvent(QMouseEvent * event)
{
	
}

int SampleMappingEditor::GetViewW()
{
	int viewportW = viewport()->geometry().width();
	return viewportW - 70;
}

int SampleMappingEditor::GetViewH()
{
	int viewportH = viewport()->geometry().height();
	return viewportH - 70;
}