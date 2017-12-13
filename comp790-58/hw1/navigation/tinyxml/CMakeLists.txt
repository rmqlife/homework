cmake_minimum_required(VERSION 2.8)

project(tinyxml)

file(
	GLOB_RECURSE
	source_files
	tinyxml.cpp
	tinystr.cpp
	tinyxmlerror.cpp
	tinyxmlparser.cpp
	*.h
)

add_library(
	tinyxml
	STATIC
	${source_files}
)

#add_executable (xmltest.exe xmltest.cpp)
#target_link_libraries (xmltest.exe tinyxml) 

SET_TARGET_PROPERTIES (tinyxml PROPERTIES DEFINE_SYMBOL  "EXPORT" )
INSTALL( FILES tinyxml.h tinystr.h DESTINATION include/ )
INSTALL( FILES ${LIBRARY_OUTPUT_PATH}/libtinyxml.so DESTINATION lib/ )
