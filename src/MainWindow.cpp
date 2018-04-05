#include "MainWindow.hpp"


MainWindow::MainWindow()
{
	setWindowTitle("RenderViewport");
	
	//Set the Top bar 
	fileMenu = menuBar()->addMenu("File");
	saveAction = fileMenu->addAction("Save");
	loadAction = fileMenu->addAction("Load");
	importAction = fileMenu->addAction("Import");
	importSequenceAction = fileMenu->addMenu("Import Sequence");
	QAction* dcmSqeuenceAction = importSequenceAction->addAction("dcm");
	QAction* tiffSequenceAction = importSequenceAction->addAction("tiff");
	QObject::connect(saveAction, SIGNAL(triggered()), this, SLOT(Save()));
	QObject::connect(loadAction, SIGNAL(triggered()), this, SLOT(Load()));
	
	
	QObject::connect(dcmSqeuenceAction, &QAction::triggered, [this]()
	{
		QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Image"), "", tr("types of Files(*)"));
		renderViewport.ImportDicomFileSequence(fileNames);
		std::cout << "Import Sequence" << std::endl;
	});
	QObject::connect(tiffSequenceAction, &QAction::triggered, [this]()
	{
		QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Image"), "", tr("types of Files(*)"));
		renderViewport.ImportTIFFFileSequence(fileNames);
		std::cout << "Import Sequence" << std::endl;
	});
		
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
