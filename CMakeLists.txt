cmake_minimum_required(VERSION 3.0.0)
set(project_name window)
project(${project_name})

set(CMAKE_CXX_FLAGS "-std=c++0x -g -Wall -Wno-endif-labels")

find_package(GLEW REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Configure RES_LOC macro in the source
set(RES_LOC ${CMAKE_BINARY_DIR}/)
configure_file(util.h.in ${CMAKE_BINARY_DIR}/generated/util.h)
# Set up resources
file(GLOB vertex_shaders "*.vs")
file(GLOB fragment_shaders "*.frag")
file(COPY ${vertex_shaders} ${fragment_shaders} DESTINATION ${RES_LOC}/shaders/)

add_definitions(${GLFW_CFLAGS_OTHER})
include_directories(${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${CMAKE_BINARY_DIR}/generated)
link_directories(${GLFW_LIBRARY_DIRS})

file(GLOB sources "*.cpp")
add_executable (${project_name} ${sources})
target_link_libraries(${project_name} ${GLFW_STATIC_LIBRARIES} ${GLEW_LIBRARY})
