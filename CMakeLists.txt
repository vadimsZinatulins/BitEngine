cmake_minimum_required(VERSION 3.20)

project(BitEngine C CXX)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_subdirectory(src)

include(CMakePackageConfigHelpers)

install(
	TARGETS BitEngine Glad
	EXPORT BitEngineTarget
	ARCHIVE
)

install(
	EXPORT BitEngineTarget
	DESTINATION lib/BitEngine/cmake	
	NAMESPACE BE::
)

install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/src/BitEngine/include/BitEngine
	DESTINATION include
)

set(LIB_CMAKE_DIR BitEngine/cmake)
set(TEMPLATE_CONFIG_FILE "${PROJECT_SOURCE_DIR}/BitEngineConfig.cmake.in")
set(CONFIG_FILE "${PROJECT_SOURCE_DIR}/build/BitEngineConfig.cmake")

configure_package_config_file(
	${TEMPLATE_CONFIG_FILE} ${CONFIG_FILE}
	INSTALL_DESTINATION lib/BitEngine
	PATH_VARS LIB_CMAKE_DIR
)

install(
	FILES ${CONFIG_FILE}
	DESTINATION lib/${LIB_CMAKE_DIR}
)
