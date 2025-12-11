cmake_minimum_required(VERSION 3.20)
project(v3_0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# DLL
add_library(grades SHARED
    grades_dll/grades.cpp
)
target_include_directories(grades PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/grades_dll)
target_compile_definitions(grades PRIVATE GRADES_DLL_EXPORTS)

# EXE
add_executable(vu_student_app
    app/main.cpp
    app/studentas.cpp
    app/resources.rc
)

# Include path'ai, kad headeriai rastųsi iš abiejų modulių
target_include_directories(vu_student_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/app
    ${CMAKE_CURRENT_SOURCE_DIR}/grades_dll
)

target_link_libraries(vu_student_app PRIVATE grades)

# Išdėstymas viename kataloge
set_target_properties(vu_student_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set_target_properties(grades       PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
