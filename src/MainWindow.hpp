#pragma once

#include "Common.hpp"

#include "RenderViewport.hpp"
#include "ControlPanel.hpp"


class MainWindow: public QMainWindow
{
	Q_OBJECT
	public:
		RenderViewport renderViewport;
		ControlPanel controlPanel;
		
		QMenu* fileMenu;
		QAction* saveAction;
		QAction* loadAction;
		QAction* importAction;
		
		MainWindow();
		void ExpandToFitScreen();
		
	signals:
		
	public slots:
		void Save();
		void Load();
		void Import();
};