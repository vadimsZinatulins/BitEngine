find_package(SDL2)
find_package(SimpleTaskManager)

add_executable(BitEngine 
	main.cpp 
	Engine.cpp
	VertexArrayObject.cpp
)

target_include_directories(BitEngine
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/BitEngine>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/BitEngine/graphics>
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

