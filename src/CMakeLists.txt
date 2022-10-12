find_package(SDL2)
find_package(SimpleTaskManager)

add_executable(BitEngine 
	main.cpp 
	Engine.cpp
	Time.cpp
	scene/SceneManager.cpp
	input/Keyboard.cpp
	input/Mouse.cpp
	graphics/VertexArrayObject.cpp
	graphics/IShader.cpp
	graphics/VertexShader.cpp
	graphics/FragmentShader.cpp
	graphics/ShaderProgram.cpp
)

target_include_directories(BitEngine
	PRIVATE
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/BitEngine>
		$<INSTALL_INTERFACE:include/BitEngine>
	INTERFACE
		$<INSTALL_INTERFACE:include>
)

target_link_libraries(BitEngine
	PRIVATE 
		${SDL2_LIBRARIES}
		STM::SimpleTaskManager
		Glad
)

