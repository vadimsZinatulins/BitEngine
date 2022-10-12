find_package(SDL2)
find_package(SimpleTaskManager)

add_library(BitEngine 
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

message("BitEngine current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(BitEngine
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/BitEngine>
		$<INSTALL_INTERFACE:include/BitEngine>
	INTERFACE
		$<INSTALL_INTERFACE:include>
)

target_link_libraries(BitEngine
	PUBLIC 
		${SDL2_LIBRARIES}
		Glad
		STM::SimpleTaskManager
)

