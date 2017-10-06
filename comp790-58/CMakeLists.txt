cmake_minimum_required(VERSION 2.8)

project(SEGMENT_DIST)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib/)
link_directories (${LIBRARY_OUTPUT_PATH}/)

#Where to find the header files
INCLUDE_DIRECTORIES (${SEGMENT_DIST}/)
INCLUDE_DIRECTORIES (${SEGMENT_DIST}/tinyxml)

set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fpermissive" )

ADD_SUBDIRECTORY(tinyxml)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SEGMENT_DIST_SOURCE_DIR}/Exe)

file(
	GLOB_RECURSE
	source_files
	segmentDist.cpp
	*.h
)

add_executable(
	segmentDist
	${source_files}
)

target_link_libraries (segmentDist tinyxml  )

