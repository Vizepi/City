cmake_minimum_required(VERSION 3.2.1)

project(City)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 11)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_SCL_SECURE_NO_WARNINGS")
else (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")
endif (MSVC)

include_directories("Include")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../Bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../Bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../Lib)

set(SOURCES_TOOLS
	Include/Vector.h
)
source_group("Tools" FILES ${SOURCES_TOOLS})

set(SOURCES_SHAPES
	Include/Shape.h
	Include/Quad.h
	Include/Triangle.h
)
source_group("Shapes" FILES ${SOURCES_SHAPES})

set(SOURCES
	${SOURCES_TOOLS}
	${SOURCES_SHAPES}
	Src/main.cpp
)

add_executable(City ${SOURCES})
