# CMakeList.txt: MMOpenGL 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

include_directories(../3rdparty/include/)

link_directories(../3rdparty/lib/glfw/)

add_library(
	MMGLShader
	"MMGLShader.hpp"
	"MMGLShader.cpp"
)