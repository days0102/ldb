project(client)

message(STATUS "Start Build Client...")
message(STATUS "Source Dir: " ${PROJECT_SOURCE_DIR})
message(STATUS "Binary Dir: " ${PROJECT_BINARY_DIR})
# 重新定义 EXECUTABLE_OUTPUT_PATH 指定目标存放位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
message(STATUS "Output Dir: " ${EXECUTABLE_OUTPUT_PATH})
message(STATUS "Lib Dir: " ${LIBRARY_OUTPUT_PATH})

FILE(GLOB_RECURSE CLIENT_SRC *.cc) # 搜索CMakeLists.txt所在目录及子目录下所有.cc文件
FOREACH(FF ${CLIENT_SRC})
    MESSAGE(${FF})
ENDFOREACH(FF)

ADD_EXECUTABLE(${PROJECT_NAME} ${CLIENT_SRC}) # 生成目标