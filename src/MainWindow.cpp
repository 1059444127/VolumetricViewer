#include "MainWindow.hpp"


MainWindow::MainWindow()
{
	setWindowTitle("RenderViewport");
	
	//Set the Top bar 
	fileMenu = menuBar()->addMenu("File");
	saveAction = fileMenu->addAction("Save");
	loadAction = fileMenu->addAction("Load");
	importAction = fileMenu->addAction("Import");
	QObject::connect(saveAction, SIGNAL(triggered()), this, SLOT(Save()));
	QObject::connect(loadAction, SIGNAL(triggered()), this, SLOT(Load()));
	QObject::connect(importAction, SIGNAL(triggered()), this, SLOT(Import()));
		
	//central
	setCentralWidget(&renderViewport);

	//dockables
	addDockWidget(Qt::LeftDockWidgetArea, &controlPanel);
	
	showNormal();
	ExpandToFitScreen();
}

void MainWindow::ExpandToFitScreen()
{
	//Expand the window to fill the avalible screen space
	QRect rec = QApplication::desktop()->availableGeometry(this);
	int differenceH = frameGeometry().height() - geometry().height();
	int differenceW = frameGeometry().width() - geometry().width();
	int height = rec.height() - differenceH;
	int width = rec.width() - differenceW;
	resize(width, height);
	move(rec.topLeft().x(), rec.topLeft().y());	
}

void MainWindow::Save()
{
	std::cout << "Save Project" << std::endl;
}

void MainWindow::Load()
{
	std::cout << "Load Project" << std::endl;
}

void MainWindow::Import()
{
	
	QString fileName;
	fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("types of Files (*.png *.jpg *.bmp)"));
	renderViewport.ImportDicomFile(fileName);
	std::cout << "Import Project" << std::endl;
}