project(net)

message(STATUS "Start Build net...")
message(STATUS "Source Dir: " ${PROJECT_SOURCE_DIR})
message(STATUS "Binary Dir: " ${PROJECT_BINARY_DIR})
# 重新定义 EXECUTABLE_OUTPUT_PATH 指定目标存放位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../bin)
# 重新定义 LIBRARY_OUTPUT_PATH 指定目标链接库存放位置
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../lib)
message(STATUS "Output Dir: " ${EXECUTABLE_OUTPUT_PATH})
message(STATUS "Lib Dir: " ${LIBRARY_OUTPUT_PATH})

FILE(GLOB_RECURSE NET_SRC *.cc) # 搜索CMakeLists.txt所在目录及子目录下所有.cc文件
FOREACH(FF ${NET_SRC})
    MESSAGE(${FF})
ENDFOREACH(FF)
# ADD_EXECUTABLE(${PROJECT_NAME} ${NET_SRC}) # 生成目标

#
# clang-tidy
#
# 搜索 clang-tidy
# find_program(CLANG_TIDY_EXE NAMES "clang-tidy-12" REQUIRED)
# 禁用了所有默认检查 (-*)，并且只启用了提倡使用现代 C++ 语言结构的检查 ( modernize-*)。
# set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=-*,modernize-*")
# 为构建目标clang-tidy设置属性
# set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")


#SHARED，动态库
#STATIC，静态库
ADD_LIBRARY(net SHARED ${NET_SRC} )
ADD_LIBRARY(net_static STATIC ${NET_SRC})

# 没有SET_TARGET_PROPERTIES， 是不能同时build 静态库和动态库， 如果只build 一种库， 就不需要这个功能
SET_TARGET_PROPERTIES(net_static PROPERTIES OUTPUT_NAME "net")
GET_TARGET_PROPERTY(OUTPUT_VALUE net_static OUTPUT_NAME)
MESSAGE(STATUS "This is the func_static OUTPUT_NAME:" ${OUTPUT_VALUE})

# 编译静态库时，自动会把同名的动态库给删除， 因此需要临时设置一下
SET_TARGET_PROPERTIES(net PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(net_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# 设置版本号 VERSION指代动态库版本，SOVERSION指代API版本


SET(MAIJOR_VER 1)
SET(MINOR_VER  0)
SET(PATCH_VER  0)
SET(OTHER_VER  1)
ADD_DEFINITIONS(-DMAIJOR_VER=${MAIJOR_VER} -DMINOR_VER=${MINOR_VER} -DPATCH_VER=${PATCH_VER} -DOTHER_VER=${OTHER_VER})

SET_TARGET_PROPERTIES(net PROPERTIES VERSION ${MAIJOR_VER}.${MINOR_VER}.${PATCH_VER} SOVERSION ${MAIJOR_VER})

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../lib)
# Target 必须在定义 ADD_EXECUTABLE 之后， programs 不受这个限制
# TARGETS和PROGRAMS 的默认权限是OWNER_EXECUTE, GROUP_EXECUTE, 和WORLD_EXECUTE，即755权限， programs 都是处理脚步类
# 类型分为RUNTIME／LIBRARY／ARCHIVE, prog
INSTALL(TARGETS net net_static
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

# 小心 安装的时候，不要变成include/func.h, 如果这样，第二次安装的时候会变成include/func.h/func.h
# INSTALL(FILES func.h DESTINATION include/)

FILE(GLOB_RECURSE ALL_HEADER  *.h)
FOREACH(F ${ALL_HEADER})
    file(RELATIVE_PATH RELAPATH_HEADER ${PROJECT_SOURCE_DIR} ${F}) # 获取相对路径
    get_filename_component(headDir ${RELAPATH_HEADER} DIRECTORY)
    MESSAGE("Install " ${RELAPATH_HEADER} " to " ${CMAKE_INSTALL_PREFIX} "/" ${PROJECT_NAME} "/include/" ${headDir})
    INSTALL(FILES ${RELAPATH_HEADER} DESTINATION include/${headDir})
ENDFOREACH(F)