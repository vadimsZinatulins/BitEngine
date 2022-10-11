find_package(SDL2)
find_package(SimpleTaskManager)

add_executable(BitEngine 
	main.cpp 
	Engine.cpp
	VertexArrayObject.cpp
	IShader.cpp
	VertexShader.cpp
	FragmentShader.cpp
	ShaderProgram.cpp
	Keyboard.cpp
)

target_include_directories(BitEngine
	PRIVATE
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/BitEngine>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/BitEngine/graphics>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/BitEngine/input>
		$<INSTALL_INTERFACE:include/BitEngine>
		$<INSTALL_INTERFACE:include/BitEngine/graphics>
	INTERFACE
		$<INSTALL_INTERFACE:include>
)

target_link_libraries(BitEngine
	PRIVATE 
		${SDL2_LIBRARIES}
		STM::SimpleTaskManager
		Glad
)

