
set (volumetricRendererSrc 
		Main.cpp
		MainWindow.cpp
		HelperWidgets.cpp
		ControlPanel.cpp
		RenderViewport.cpp
)

add_executable(VolumetricRenderer ${volumetricRendererSrc})

target_link_libraries(VolumetricRenderer Qt5::Core Qt5::Widgets Qt5::OpenGL)