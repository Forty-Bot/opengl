cmake_minimum_required(VERSION 3.0.0)
set(project_name window)
project(${project_name})

set(CMAKE_CXX_FLAGS "-std=c++0x -g")

find_package(GLEW REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_definitions(${GLFW_CFLAGS_OTHER})
include_directories(${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

add_executable (${project_name} window.cpp)
target_link_libraries(${project_name} ${GLFW_STATIC_LIBRARIES} ${GLEW_LIBRARY})

message(STATUS ${EXTRA_LIBS})
message(STATUS ${GLEW_LIBRARY})
message(STATUS ${GLFW_LIBRARIES})
