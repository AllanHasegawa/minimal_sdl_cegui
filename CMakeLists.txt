cmake_minimum_required(VERSION 2.8)
project(minimal_sdl_cegui)

# Could not find a good FindCEGUI.cmake file T_T
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
#find_package(CEGUI 0.8)

# hard coding CEGUI links for Gentoo 64 bits
set(CEGUI_INCLUDE_DIRS "/usr/include/cegui-0")
set(CEGUI_LIBRARIES "/usr/lib64/libCEGUIBase-0.so")
set(CEGUI_OPENGL_LIBRARIES "/usr/lib64/libCEGUIOpenGLRenderer-0.so")
include_directories(${CEGUI_INCLUDE_DIRS})

find_package(PkgConfig REQUIRED)

pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
	message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRCS
	main.cpp
)

add_executable(app ${SRCS})
target_link_libraries(app ${CEGUI_LIBRARIES} ${CEGUI_OPENGL_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})

add_custom_command(TARGET app POST_BUILD COMMAND
	ln -sf ${CMAKE_SOURCE_DIR}/datafiles
	${CMAKE_BINARY_DIR}/datafiles)
