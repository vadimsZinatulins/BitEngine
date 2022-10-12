add_library(Glad glad.c)

message("Glad project source dir: ${PROJECT_SOURCE_DIR}")

target_include_directories(Glad 
	PUBLIC 
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

