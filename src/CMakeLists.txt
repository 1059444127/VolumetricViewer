
set (volumetricRendererSrc 
		Main.cpp
		MainWindow.cpp
		HelperWidgets.cpp
		ControlPanel.cpp
		RenderViewport.cpp
		
		Renderer/Texture3D.cpp
		Renderer/Object3D.cpp
		Renderer/TextureVolumeObject.cpp
		Renderer/CameraObject.cpp
)

add_executable(VolumetricRenderer ${volumetricRendererSrc})

target_link_libraries(VolumetricRenderer Qt5::Core Qt5::Widgets Qt5::OpenGL)