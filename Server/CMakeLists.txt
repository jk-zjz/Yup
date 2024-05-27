cmake_minimum_required(VERSION 3.5)
project(untitled)

#设置需要查找动态库的目录
set(LINK_K " /usr/local/lib/ /usr/lib/ /usr/lib64/ /usr/lib64/mysql/")
set(CJSON_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/lib/json")
set(INIPARSER_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/lib/iniparser/")
set(MYSQL_LIBRARY_DIR "/usr/lib64/mysql/")
set(CRYPTO_LIBRARY_DIR "/usr/lib64/")

#读取./common 下的源文件
aux_source_directory("./common" CPP_G)

#读取头文件的目录
include_directories("./include/"
                    "/usr/include/fastdfs/"
                    "/usr/include/fastcommon"
                    "./include/cjson/"
                    "./include/iniparser/"
                    "/usr/local/include/hiredis/"
)
#寻找 .so 动态库
find_library(FASTCOMMON  fastcommon  ${LINK_K})
find_library(FDFSCLIENT  fdfsclient  ${LINK_K})
find_library(HIREDIS  hiredis  ${LINK_K})
find_library(JWT  jwt  ${LINK_K})

#、读取文件demo
add_executable(file_demo ./test/echo.c ${CPP_G})
set_target_properties(file_demo
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        ./bin
)
target_link_libraries(file_demo fcgi
        ${FASTCOMMON}
        ${FDFSCLIENT}
        ${CJSON_LIBRARY_DIR}/libcjson.so
        ${JWT}
        ${INIPARSER_LIBRARY_DIR}/libiniparser.so.1
        ${MYSQL_LIBRARY_DIR}/libmysqlclient.so.21
        ${CRYPTO_LIBRARY_DIR}/libcrypto.so
        ${HIREDIS}
)

#测试编译生成
add_executable(test ./test/mina.c ${CPP_G})
set_target_properties(test
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        ./bin
)
target_link_libraries(test fcgi
        ${FASTCOMMON}
        ${FDFSCLIENT}
        ${CJSON_LIBRARY_DIR}/libcjson.so
        ${JWT}
        ${INIPARSER_LIBRARY_DIR}/libiniparser.so.1
        ${MYSQL_LIBRARY_DIR}/libmysqlclient.so.21
        ${CRYPTO_LIBRARY_DIR}/libcrypto.so
        ${HIREDIS}
)

#客户端登录请求
add_executable(login test/login.c ${CPP_G})
set_target_properties(login
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        ./bin
)
target_link_libraries(login fcgi
        ${FASTCOMMON}
        ${FDFSCLIENT}
        ${CJSON_LIBRARY_DIR}/libcjson.so
        ${JWT}
        ${INIPARSER_LIBRARY_DIR}/libiniparser.so.1
        ${MYSQL_LIBRARY_DIR}/libmysqlclient.so.21
        ${CRYPTO_LIBRARY_DIR}/libcrypto.so
        ${HIREDIS}
)

#客户端注册请求
add_executable(register test/register.c ${CPP_G})
set_target_properties(register
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        ./bin
)
target_link_libraries(register fcgi
        ${FASTCOMMON}
        ${FDFSCLIENT}
        ${CJSON_LIBRARY_DIR}/libcjson.so
        ${JWT}
        ${INIPARSER_LIBRARY_DIR}/libiniparser.so.1
        ${MYSQL_LIBRARY_DIR}/libmysqlclient.so.21
        ${CRYPTO_LIBRARY_DIR}/libcrypto.so
        ${HIREDIS}
        )

#内部数据请求
add_executable(userinfo test/userinfo.c ${CPP_G})
set_target_properties(userinfo
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        ./bin
)
target_link_libraries(userinfo fcgi
        ${FASTCOMMON}
        ${FDFSCLIENT}
        ${CJSON_LIBRARY_DIR}/libcjson.so
        ${JWT}
        ${INIPARSER_LIBRARY_DIR}/libiniparser.so.1
        ${MYSQL_LIBRARY_DIR}/libmysqlclient.so.21
        ${CRYPTO_LIBRARY_DIR}/libcrypto.so
        ${HIREDIS}
)

