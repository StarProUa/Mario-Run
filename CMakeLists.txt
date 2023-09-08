cmake_minimum_required(VERSION 3.5)

project(Mario-Run LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/GLFW)
add_subdirectory(external/plog)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(external/stb)
#include_directories(external/plog)

set(SRC
    src/main.cpp
    src/player.cpp
    src/map.cpp
    src/func.cpp
    src/application.cpp
    # headers
    src/player.h
    src/map.h
    src/func.h
    src/application.h
    src/entity.h
)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw plog)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/Mario-Run/assets
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Mario-Run/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

include(GNUInstallDirs)
