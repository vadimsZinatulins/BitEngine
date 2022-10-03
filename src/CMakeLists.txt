find_package(SDL2)
find_package(SimpleTaskManager)

add_executable(BitEngine main.cpp Engine.cpp)

target_include_directories(BitEngine
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/BitEngine>
		$<INSTALL_INTERFACE:include/BitEngine>
	INTERFACE
		$<INSTALL_INTERFACE:include>
)

target_link_libraries(BitEngine
	PRIVATE 
		STM::SimpleTaskManager
		${SDL2_LIBRARIES}
)
