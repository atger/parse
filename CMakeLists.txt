cmake_minimum_required ( VERSION 3.9 )
project (sml)

set (CMAKE_CXX_STANDARD 11)

# Set the output folder where your library will be created
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# The following folder will be included
include_directories(src include)

add_library( sml STATIC
		src/string_utils.cpp
		src/Fastq.cpp
		)

