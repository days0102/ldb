cmake_minimum_required(VERSION 3.15) # cmake最低版本
set(CXX_STANDARD 17)    # 使用c++17
set(CMAKE_CXX_FLAGS "-g -Wall")# debug
project(ldb)    # 项目名称

message(STATUS "Start Build ...")
message(STATUS "Source Dir: " ${PROJECT_SOURCE_DIR})
message(STATUS "Binary Dir: " ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_DIR ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_DIR ${PROJECT_BINARY_DIR}/lib)
message(STATUS "Output Dir: " ${EXECUTABLE_OUTPUT_DIR})
message(STATUS "Lib Dir: " ${LIBRARY_OUTPUT_DIR})


include_directories(${PROJECT_SOURCE_DIR})
# get_property(dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
# message(">>> include_dirs=${dirs}") #打印一下目录情况

# 添加子目录下的 CMakeLists
add_subdirectory(src)
add_subdirectory(lib)
