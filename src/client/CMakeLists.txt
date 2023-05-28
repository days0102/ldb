project(client)

message(STATUS "Start Build Client...")
message(STATUS "Source Dir: " ${PROJECT_SOURCE_DIR})
message(STATUS "Binary Dir: " ${PROJECT_BINARY_DIR})
# 重新定义 EXECUTABLE_OUTPUT_PATH 指定目标存放位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../bin)
# 重定义库输出目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../lib)
message(STATUS "Output Dir: " ${EXECUTABLE_OUTPUT_PATH})
message(STATUS "Lib Dir: " ${LIBRARY_OUTPUT_PATH})


FILE(GLOB_RECURSE CLIENT_SRC *.cc) # 搜索CMakeLists.txt所在目录及子目录下所有.cc文件
FOREACH(FF ${CLIENT_SRC})
MESSAGE(${FF})
ENDFOREACH(FF)

# include_directories(${PROJECT_SOURCE_DIR}/../../inc)
# target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../inc)
# get_property(dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
# message(">>> include_dirs=${dirs}") #打印一下目录情况

set(LIBS net) # 添加库

ADD_EXECUTABLE(${PROJECT_NAME} ${CLIENT_SRC}) # 生成目标
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBS}) # 链接库
#
# clang-tidy
#
# 搜索 clang-tidy
find_program(CLANG_TIDY_EXE NAMES "clang-tidy-12" REQUIRED)
# 禁用了所有默认检查 (-*)，并且只启用了提倡使用现代 C++ 语言结构的检查 ( modernize-*)。
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=-*,modernize-*")
# 为构建目标clang-tidy设置属性
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")