project(server)

MESSAGE(STATUS "Start Build Server...")

FILE(GLOB_RECURSE SERVER_SRC *.cc) # 搜索CMakeLists.txt所在目录及子目录下所有.cc文件
FOREACH(FF ${SERVER_SRC})
    MESSAGE(${FF})
ENDFOREACH(FF)

ADD_EXECUTABLE(${PROJECT_NAME} ${SERVER_SRC}) # 生成目标