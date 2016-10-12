cmake_minimum_required(VERSION 3.6)
project(ASR5_MiniProjet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_custom_target(ASR5_MiniProjet COMMAND make -C ${ASR5_MiniProjet_SOURCE_DIR}
        CLION_EXE_DIR=${PROJET_BINARY_DIR})
#set(SOURCE_FILES main.cpp)
#add_executable(ASR5_MiniProjet ${SOURCE_FILES})