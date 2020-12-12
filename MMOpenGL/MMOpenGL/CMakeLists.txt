# CMakeList.txt: MMOpenGL 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

include_directories(../3rdparty/include/)

link_directories(../3rdparty/lib/glfw/)
link_directories("${CMAKE_BINARY_DIR}/lib")

add_definitions(-std=c++11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


# 将源代码添加到此项目的可执行文件。
add_executable (MMOpenGL 
	"MMOpenGL.cpp" 
	"MMOpenGL.hpp" )

target_link_libraries(MMOpenGL glfw3)
target_link_libraries(MMOpenGL MMHelloStatic)
target_link_libraries(MMOpenGL MMGLShader)
target_link_libraries(MMOpenGL glad)
