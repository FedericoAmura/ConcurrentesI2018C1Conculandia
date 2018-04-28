cmake_minimum_required(VERSION 3.10)
project(aduanaconculandia)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

add_subdirectory("${PROJECT_SOURCE_DIR}/Util")

add_executable(aduanaconculandia ${SOURCE} ${HEADERS})