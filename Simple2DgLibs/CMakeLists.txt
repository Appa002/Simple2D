cmake_minimum_required(VERSION 3.10)
project(Simple2DgLibs)

set(CMAKE_CXX_STANDARD 17)

ADD_COMPILE_OPTIONS(-fPIC)

add_library(Simple2DgLibs SHARED index.cpp Simple2D.h Simple2D.cpp)

set_target_properties(Simple2DgLibs PROPERTIES PREFIX "")
set_target_properties(Simple2DgLibs PROPERTIES OUTPUT_NAME "external")

add_custom_command(TARGET Simple2DgLibs
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/update.sh
        )