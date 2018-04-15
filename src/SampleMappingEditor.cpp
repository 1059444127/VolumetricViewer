#include "SampleMappingEditor.hpp"


//
//SampleMappingNode
//


SampleMappingNode::SampleMappingNode(double x, double y)
{
	selected = false;
	setZValue(3);
	xPos = x;
	yPos = y; 
	color = QColor(128, 128, 128);
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
	int sceneX = xPos * viewW;
	int sceneY = yPos * viewH;
	
	QColor colorBorder = QColor(255, 255, 255);
	if(selected) colorBorder = QColor(255, 122, 122);
	
	painter->setPen(QPen(colorBorder));
	painter->setBrush(QBrush(color, Qt::SolidPattern));
	painter->drawEllipse(-5, -5, 10, 10);
}


//
//SampleMappingHistogram
//


SampleMappingHistogram::SampleMappingHistogram()
{
	setZValue(1);
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
	painter->setBrush(QBrush(QColor(100, 100, 100, 100), Qt::SolidPattern));
	painter->setPen(QPen(QColor(100, 100, 100, 100), Qt::SolidPattern));
	for(int i = 0; i < data.size(); i++)
	{
		int x = (double)i / ((double)data.size() - 1.0)  *  viewW;
		int y = (double)data[i] / 255.0  *  viewH;
		int W = (double)(i+1) / ((double)data.size() - 1.0)  *  viewW - x;
		painter->drawRect(x, 0, (std::max)(W, 1), -y);
	}
}

void SampleMappingHistogram::SetData(unsigned char* d, int len)
{
	data.resize(len);
	for(int i = 0; i < len; i++)
	{
		data[i] = d[i]; 
	}
	
	
}


//
//SampleMappingCurve
//


SampleMappingCurve::SampleMappingCurve()
{
	setZValue(2);
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
	painter->setRenderHint(QPainter::Antialiasing);
	
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
		
		//add to start and end to unbound
		points.insert(points.begin(), QPointF(0, points[0].y()));
		points.push_back(QPointF(viewW, points[points.size() - 1].y()));
		
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
	else
	{
		//path.moveTo(QPointF(0, 0));
		//double x = viewW;
		//double y = 0;
		//path.cubicTo(QPointF(x, y), QPointF(x, y), QPointF(x, y));
	}

	QPen pen; 
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(2);
	pen.setColor(Qt::white);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	
	painter->setPen(pen);
	
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
	prevNodeColor = QColor(255, 255, 255);
	 
	selectedNode = NULL;
	
	scene = new QGraphicsScene(this);
	
	setScene(scene);
	
	setInteractive(true); 
	
	histogram = new SampleMappingHistogram;
	scene->addItem(histogram);
	
	//unsigned char d[256];
	//for(int i = 0; i < 256; i++) d[i] = i;
	//histogram->SetData(d, 256);///Test Data
	
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
	curve->viewW = GetViewW();
	curve->viewH = GetViewH();
	histogram->viewW = GetViewW();
	histogram->viewH = GetViewH();
	
	
	Reset();
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
	
	histogram->viewW = GetViewW();
	histogram->viewH = GetViewH();
	
	for(int i = 0; i < nodes.size(); i++)
	{
		nodes[i]->viewW = GetViewW();
		nodes[i]->viewH = GetViewH();
		QPointF pointInScene = QPointF(nodes[i]->viewW * nodes[i]->xPos, -nodes[i]->viewH * nodes[i]->yPos);
		nodes[i]->setPos(pointInScene);
	}
	
}

void SampleMappingEditor::mouseDoubleClickEvent(QMouseEvent * event)
{
	if(event->button() == Qt::LeftButton)
	{
		int mouseX = event->x();
		int mouseY = event->y();
		QPointF pointInScene = mapToScene(QPoint(mouseX, mouseY));
		pointInScene.setX((std::max)(0.0f, (float)pointInScene.x())); 
		pointInScene.setY((std::min)(0.0f, (float)pointInScene.y())); 
		pointInScene.setX((std::min)((float)GetViewW(), (float)pointInScene.x())); 
		pointInScene.setY((std::max)(-(float)GetViewH(), (float)pointInScene.y())); 
		double x = pointInScene.x() / GetViewW();
		double y = -pointInScene.y() / GetViewH();
		SampleMappingNode* newNode = new SampleMappingNode(x, y);
		newNode->setPos(pointInScene);
		newNode->viewW = GetViewW();
		newNode->viewH = GetViewH();
		nodes.push_back(newNode);
		scene->addItem(newNode);
		
		scene->update(); 
		update(); 
		emit CurveChanged();
		
		std::cout << "Added New Node at " << x << ", " << y << std::endl; 
	}
}

void SampleMappingEditor::mousePressEvent(QMouseEvent * event)
{
	QGraphicsView::mousePressEvent(event);
	
	if(event->button() == Qt::LeftButton)
	{
		QGraphicsItem* item = itemAt(event->pos());
		
		for(int i = 0; i < nodes.size(); i++)
			nodes[i]->selected = false;
		
		selectedNode = NULL;
		
		if(item)
		{
			SampleMappingNode* n = qgraphicsitem_cast<SampleMappingNode*>(item);			
			if(n != 0)
			{
				std::cout << "Node Selected" << std::endl;
				n->selected = true;
				selectedNode = n;
			}
		}
		
		update();
		scene->update(); 
		emit CurveChanged();
	}
	
	if(event->button() == Qt::RightButton)
	{
		QGraphicsItem* item = itemAt(event->pos());
		
		for(int i = 0; i < nodes.size(); i++)
			nodes[i]->selected = false;
		
		selectedNode = NULL;
		
		if(item)
		{
			SampleMappingNode* n = qgraphicsitem_cast<SampleMappingNode*>(item);			
			if(n != 0)
			{
				std::cout << "Node Selected" << std::endl;
				n->selected = true;
				selectedNode = n;
				
				QColor col = QColorDialog::getColor(prevNodeColor, this, "Choose Color Stop");
				if(col.isValid())
				{
					selectedNode->color = col;
					prevNodeColor = col; 
				}
			}
		}
		
		update();
		scene->update(); 
		emit CurveChanged();
	}
}

void SampleMappingEditor::mouseMoveEvent(QMouseEvent * event)
{

	if(selectedNode != NULL)
	{
		int mouseX = event->x();
		int mouseY = event->y();
		QPointF pointInScene = mapToScene(QPoint(mouseX, mouseY));
		
		pointInScene.setX((std::max)(0.0f, (float)pointInScene.x())); 
		pointInScene.setY((std::min)(0.0f, (float)pointInScene.y())); 
		pointInScene.setX((std::min)((float)GetViewW(), (float)pointInScene.x())); 
		pointInScene.setY((std::max)(-(float)GetViewH(), (float)pointInScene.y())); 
		
		double x = pointInScene.x() / GetViewW();
		double y = -pointInScene.y() / GetViewH();
		selectedNode->setPos(pointInScene);
		selectedNode->xPos = x;
		selectedNode->yPos = y; 
		
		update();
		scene->update(); 
		emit CurveChanged();
	}	
}

void SampleMappingEditor::keyPressEvent(QKeyEvent* event)
{
	if(event->key() == Qt::Key_Delete)
	{
		if(selectedNode != NULL)
		{
			for(int i = 0; i < nodes.size(); i++)
			{
				if(nodes[i] == selectedNode)
				{
					delete selectedNode; 
					selectedNode = NULL; 
					nodes.erase(nodes.begin() + i);
					break; 
				}
			}
			
			update();
			scene->update(); 
			emit CurveChanged();
		}
	}
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

void SampleMappingEditor::Reset()
{
	selectedNode = NULL; 
	
	for(int i = nodes.size()-1; i >= 0; i--)
	{
		nodes.erase(nodes.begin() + i);
	}
	
	SampleMappingNode* newNode = new SampleMappingNode(0, 0);
	newNode->setPos(0, 0);
	newNode->viewW = GetViewW();
	newNode->viewH = GetViewH();
	newNode->color = QColor(0, 0, 0);
	nodes.push_back(newNode);
	scene->addItem(newNode);
	
	SampleMappingNode* newNode2 = new SampleMappingNode(1, 1);
	newNode2->setPos(GetViewW(), GetViewH());
	newNode2->viewW = GetViewW();
	newNode2->viewH = GetViewH();
	newNode2->color = QColor(255, 255, 255);
	nodes.push_back(newNode2);
	scene->addItem(newNode2);
	
	scene->update(); 
	update(); 
	emit CurveChanged();
	
}

QColor LerpColor(QColor& a, QColor& b, double frac)
{
	return QColor(
		255 * ((b.redF() - a.redF()) * frac + a.redF()),
		255 * ((b.greenF() - a.greenF()) * frac + a.greenF()),
		255 * ((b.blueF() - a.blueF()) * frac + a.blueF())
	);
}

struct MappingPoint
{
	double x;
	double y;
	QColor color;
};

void SampleMappingEditor::GetLUT(int textureWidth, float* textureBuffer)
{
	int viewW = GetViewW();
	int viewH = GetViewH();
	
	if(nodes.size() > 0)
	{
		std::vector<MappingPoint> points; 
		for(int i = 0; i < nodes.size(); i++)
		{
			double x = nodes[i]->xPos;
			double y = nodes[i]->yPos;
			MappingPoint point; 
			point.x = x;
			point.y = y;
			point.color = nodes[i]->color; 
			points.push_back(point);
		}
		
		sort( points.begin( ), points.end( ), [ ]( const MappingPoint& lhs, const MappingPoint& rhs )
		{
		   return lhs.x < rhs.x;
		});
		
		//add to start and end to unbound
		MappingPoint startPoint;
		startPoint.x = 0;
		startPoint.y = points[0].y;
		startPoint.color = points[0].color;
		points.insert(points.begin(), startPoint);
		
		MappingPoint endPoint; 
		endPoint.x = 1.0; 
		endPoint.y = points[points.size() - 1].y;
		endPoint.color = points[points.size() - 1].color;
		points.push_back(endPoint);
		
		for(int i = 1; i < points.size(); i++)
		{
			double x0 = points[i-1].x;
			double y0 = points[i-1].y;
			double x1 = points[i].x;
			double y1 = points[i].y;
			QColor col0 = points[i-1].color;
			QColor col1 = points[i].color;
			
			int offset = x0 * textureWidth;
			int len = (x1-x0) * textureWidth;
			
			//std::cout << "adding data in range " << offset << " " << len << std::endl;
			
			for(int j = offset; j < offset + len; j++)
			{
				double frac = (double)(j - offset) / ((double)len); 
				QColor col = LerpColor(col0, col1, frac);
				textureBuffer[j * 4 + 0] = (double)col.red() / 255.0;
				textureBuffer[j * 4 + 1] = (double)col.green() / 255.0;
				textureBuffer[j * 4 + 2] = (double)col.blue() / 255.0;
				textureBuffer[j * 4 + 3] = (frac * (y1 - y0) + y0); 
			}
		}
	}
	else
	{
		for(int i = 0; i < textureWidth; i++)
		{
			double frac = (double)(i) / ((double)textureWidth); 
			textureBuffer[i*4 + 0] = frac;
			textureBuffer[i*4 + 1] = frac;
			textureBuffer[i*4 + 2] = frac;
			textureBuffer[i*4 + 3] = frac;
		}
	}
	
	
}