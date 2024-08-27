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

project(UtilsCPP)
enable_language(CXX)

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

if (UTILSCPP_BUILD_TESTS)
    add_subdirectory(tests)
endif()