project(server)

message(STATUS "Start Build Server...")
message(STATUS "Source Dir: " ${PROJECT_SOURCE_DIR})
message(STATUS "Binary Dir: " ${PROJECT_BINARY_DIR})
# 重新定义 EXECUTABLE_OUTPUT_PATH 指定目标存放位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../bin)
# 重新定义 LIBRARY_OUTPUT_PATH 指定目标链接库存放位置
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../lib)
message(STATUS "Output Dir: " ${EXECUTABLE_OUTPUT_PATH})
message(STATUS "Lib Dir: " ${LIBRARY_OUTPUT_PATH})

FILE(GLOB_RECURSE SERVER_SRC *.cc) # 搜索CMakeLists.txt所在目录及子目录下所有.cc文件
FOREACH(FF ${SERVER_SRC})
    MESSAGE(${FF})
ENDFOREACH(FF)
ADD_EXECUTABLE(${PROJECT_NAME} ${SERVER_SRC}) # 生成目标

#
# clang-tidy
#
# 搜索 clang-tidy
find_program(CLANG_TIDY_EXE NAMES "clang-tidy-12" REQUIRED)
# 禁用了所有默认检查 (-*)，并且只启用了提倡使用现代 C++ 语言结构的检查 ( modernize-*)。
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=-*,modernize-*")
# 为构建目标clang-tidy设置属性
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")