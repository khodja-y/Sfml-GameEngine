
add_definitions(-g)

file (GLOB_RECURSE SRC	
	*.cpp
)

build_chapter(PROJET SOURCES ${SRC})
