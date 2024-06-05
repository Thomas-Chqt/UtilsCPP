# ---------------------------------------------------
# CMakeLists.txt
#
# Author: Thomas Choquet <thomas.publique@icloud.com>
# Date: 2024/04/22 13:35:56
# ---------------------------------------------------

cmake_minimum_required(VERSION 3.16)

option(BUILD_SHARED_LIBS      "Build using shared libraries"          OFF)
option(UTILSCPP_INCLUDE_TESTS "Inlcude UtilsCPP tests in the project" OFF)

project(UtilsCPP CXX)

add_library(UtilsCPP)

set_target_properties(UtilsCPP PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE UTILSCPP_SRC "src/*.cpp" "src/*.tpp" "include/*.tpp" "src/*.hpp" "include/*.hpp")

target_sources(UtilsCPP PRIVATE ${UTILSCPP_SRC})

target_include_directories(UtilsCPP PRIVATE "src" PUBLIC "include")

if (UTILSCPP_INCLUDE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()