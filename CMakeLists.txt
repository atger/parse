cmake_minimum_required ( VERSION 3.9 )
project (parse)

set (CMAKE_CXX_STANDARD 17)

# Set the output folder where your library will be created
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# The following folder will be included
include_directories(src include)

add_library( parse STATIC
		src/string_utils.cpp
		src/Fastq.cpp
		)

include(gtest)
enable_testing()

set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
include_directories($(GTEST_INCLUDE_DIRS))
file(GLOB_RECURSIVE TEST_SRC_FILES RELATIVE
	${PROJECT_SOURCE_DIR}
	test/*.cpp)
message(STATUS "Test case source files: " ${TEST_SRC_FILES})
add_dependencies(${PROJECT_TEST_NAME} googletest)
add_dependencies(${PROJECT_TEST_NAME} ${PROJECT_NAME})
