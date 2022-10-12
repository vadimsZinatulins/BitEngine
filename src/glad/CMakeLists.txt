add_library(Glad glad.c)

message("BitEngine current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(Glad 
	PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

