cmake_minimum_required( VERSION 3.2 )

#project name
project( Dharahara VERSION 1.0.0 LANGUAGES C CXX )

#CXX VERSION
set( CMAKE_CXX_STANDARD 11 )
Set( CMAKE_CXX_STANDARD_REQUIRED TRUE )

#files to include
#source files
file( GLOB SRC src/*.cpp externals/glad/src/glad.c externals/stb_image/stb_image.cpp)

#header files
file( GLOB INCLUDES includes/ externals/glad/include/* externals/glm/** externals/stb_image/stb_image.cpp )

include_directories(
    ${CMAKE_SOURCE_DIR}/includes/
    ${CMAKE_SOURCE_DIR}/externals/
    ${CMAKE_SOURCE_DIR}/externals/glad/include/
    ${CMAKE_SOURCE_DIR}/externals/stb_image/
)

#executable
add_executable( ${PROJECT_NAME} src/main.cpp ${SRC} ${INCLUDES} )

#dependencies
target_link_libraries( ${PROJECT_NAME} assimp glfw GL dl)