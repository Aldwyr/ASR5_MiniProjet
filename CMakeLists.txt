cmake_minimum_required(VERSION 3.6)
project(client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_custom_target(ASR5_MiniProjet COMMAND make -C ${ASR5_MiniProjet_SOURCE_DIR}
        CLION_EXE_DIR=${PROJET_BINARY_DIR})
#file(
#        GLOB_RECURSE
#        source_files
#        src/client/*
#)

#set(EXECUTABLE_OUTPUT_PATH bin/client/)

#set(SOURCE_FILES_CLIENT src/client/^*.c)
#set(SOURCE_FILE_SERVEUR src/serveur/^*.c)
#add_executable(client ${SOURCE_FILES_CLIENT})