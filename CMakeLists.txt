# ---------------------------------------------------
# CMakeLists.txt
#
# Author: Thomas Choquet <thomas.publique@icloud.com>
# Date: 2024/04/22 13:35:56
# ---------------------------------------------------

cmake_minimum_required(VERSION 3.16)

enable_testing()

option(BUILD_SHARED_LIBS    "Build using shared libraries"          OFF)
option(UTILSCPP_BUILD_TESTS "Inlcude UtilsCPP tests in the project" OFF)

if(NOT UTILSCPP_LIBRARY_TYPE)
    if(BUILD_SHARED_LIBS)
        set(UTILSCPP_LIBRARY_TYPE SHARED)
    else()
        set(UTILSCPP_LIBRARY_TYPE STATIC)
    endif()
endif()

project(UtilsCPP)
enable_language(CXX)

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif()

if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif()

add_library(UtilsCPP ${UTILSCPP_LIBRARY_TYPE})
set_target_properties(UtilsCPP
    PROPERTIES CXX_STANDARD 11
    CXX_STANDARD_REQUIRED   ON
    CXX_VISIBILITY_PRESET   hidden
)

file(GLOB_RECURSE UTILSCPP_SRC "src/*" "include/*")
target_sources(UtilsCPP PRIVATE ${UTILSCPP_SRC})

target_include_directories(UtilsCPP PRIVATE "src" PUBLIC "include")

target_compile_definitions(UtilsCPP PRIVATE UTILSCPP_API_IMPLEMENTATION)
if(UTILSCPP_LIBRARY_TYPE STREQUAL SHARED)
    target_compile_definitions(UtilsCPP INTERFACE UTILSCPP_DLL_LINK)
endif()

if (UTILSCPP_BUILD_TESTS)
    add_subdirectory(tests)
endif()