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

set(SOURCES_RANDOM Src/Random.cpp Include/Random.h)
source_group("Tools\\Random" FILES ${SOURCES_RANDOM})

set(SOURCES_VECTOR Include/Vector.h)
source_group("Tools\\Vector" FILES ${SOURCES_VECTOR})

set(SOURCES_TOOLS
	${SOURCES_VECTOR}
	${SOURCES_RANDOM}
)

set(SOURCES_QUAD Src/Quad.cpp Include/Quad.h)
source_group("Shapes\\Quad" FILES ${SOURCES_QUAD})

set(SOURCES_TRIANGLE Src/Triangle.cpp Include/Triangle.h)
source_group("Shapes\\Triangle" FILES ${SOURCES_TRIANGLE})

set(SOURCES_LINE Src/Line.cpp Include/Line.h)
source_group("Shapes\\Line" FILES ${SOURCES_LINE})

set(SOURCES_SHAPES
	Include/Shape.h
)
source_group("Shapes" FILES ${SOURCES_SHAPES})

set(SOURCES
	${SOURCES_TOOLS}
	${SOURCES_LINE}
	${SOURCES_SHAPES}
	${SOURCES_QUAD}
	${SOURCES_TRIANGLE}
	Src/main.cpp
)

add_executable(City ${SOURCES})
