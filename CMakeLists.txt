cmake_minimum_required(VERSION 3.10)
project(aduanaconculandia)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)


add_subdirectory("${PROJECT_SOURCE_DIR}/MinistroSeguridad")
add_subdirectory("${PROJECT_SOURCE_DIR}/Util")
add_subdirectory("${PROJECT_SOURCE_DIR}/Fifos")
add_subdirectory("${PROJECT_SOURCE_DIR}/Lock")
add_subdirectory("${PROJECT_SOURCE_DIR}/Logger")
add_subdirectory("${PROJECT_SOURCE_DIR}/Printer")
add_subdirectory("${PROJECT_SOURCE_DIR}/ProcesoHijo")
add_subdirectory("${PROJECT_SOURCE_DIR}/Signal")
add_subdirectory("${PROJECT_SOURCE_DIR}/Ventanilla")
add_subdirectory("${PROJECT_SOURCE_DIR}/Persona")
add_subdirectory("${PROJECT_SOURCE_DIR}/FilaEspera")
add_subdirectory("${PROJECT_SOURCE_DIR}/Semaforo")
add_subdirectory("${PROJECT_SOURCE_DIR}/PortaSellos")
add_subdirectory("${PROJECT_SOURCE_DIR}/Sello")

add_executable(aduanaconculandia ${SOURCE} ${HEADERS})