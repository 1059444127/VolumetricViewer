#include "MainWindow.hpp"


MainWindow::MainWindow()
{
	setWindowTitle("RenderViewport");
	
	//Set the Top bar 
	fileMenu = menuBar()->addMenu("File");
	saveAction = fileMenu->addAction("Save");
	loadAction = fileMenu->addAction("Load");
	importAction = fileMenu->addAction("Import");
	importSequenceAction = fileMenu->addAction("Import Sequence");
	QObject::connect(saveAction, SIGNAL(triggered()), this, SLOT(Save()));
	QObject::connect(loadAction, SIGNAL(triggered()), this, SLOT(Load()));
	QObject::connect(importAction, SIGNAL(triggered()), this, SLOT(Import()));
	QObject::connect(importSequenceAction, SIGNAL(triggered()), this, SLOT(ImportSequence()));
		
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
	std::cout << "Save" << std::endl;
}

void MainWindow::Load()
{
	std::cout << "Load" << std::endl;
}

void MainWindow::Import()
{
	
	QString fileName;
	fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("types of Files(*.dcm)"));
	renderViewport.ImportDicomFile(fileName);
	std::cout << "Import" << std::endl;
}

void MainWindow::ImportSequence()
{
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Image"), "", tr("types of Files(*.dcm)"));
	renderViewport.ImportDicomFileSequence(fileNames);
	std::cout << "Import Sequence" << std::endl;
}