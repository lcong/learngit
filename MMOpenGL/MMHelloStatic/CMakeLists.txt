message("Test Dir: ${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
message("Test Dir: ${CMAKE_LIBRARY_OUT_DIR}")

include_directories(../3rdparty/include/)
add_library(MMHelloStatic STATIC "MMHelloStatic.cpp" "MMHelloStatic.hpp"  )
