cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(Phong-Lighting-Model-Example)

file(GLOB_RECURSE SOURCE_FILES
		${CMAKE_SOURCE_DIR}/src/*.c
		${CMAKE_SOURCE_DIR}/src/*.cpp
		${CMAKE_SOURCE_DIR}/src/imgui/*
		${CMAKE_SOURCE_DIR}/shaders/*)

file(GLOB_RECURSE HEADER_FILES
		${CMAKE_SOURCE_DIR}/src/*.h
		${CMAKE_SOURCE_DIR}/src/*.hpp)
		
		
# Specify where linker should look for static libraries for our project. 
# It’s done using link_directories command and passing the directory as a parameter.
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
)

#Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa
	-framework OpenGL -framework IOKit -framework CoreVideo")
endif()

configure_file(src/utils/root_dir.h.in src/utils/root_dir.h)
include_directories(${CMAKE_BINARY_DIR}/src)

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})

# GLAD
add_library(GLAD "thirdparty/glad.c")

# Put all libraries into a variable
set(LIBS glfw3 GLAD)

# Define the link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})
