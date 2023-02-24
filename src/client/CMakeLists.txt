project(client)

MESSAGE(STATUS "Start Build Client...")

FILE(GLOB_RECURSE CLIENT_SRC *.cc) # 搜索CMakeLists.txt所在目录及子目录下所有.cc文件
FOREACH(FF ${CLIENT_SRC})
    MESSAGE(${FF})
ENDFOREACH(FF)

ADD_EXECUTABLE(${PROJECT_NAME} ${CLIENT_SRC}) # 生成目标