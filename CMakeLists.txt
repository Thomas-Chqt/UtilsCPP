# ---------------------------------------------------
# CMakeLists.txt
#
# Author: Thomas Choquet <thomas.publique@icloud.com>
# Date: 2024/04/22 13:35:56
# ---------------------------------------------------

cmake_minimum_required(VERSION 3.23)

get_directory_property(hasParent PARENT_DIRECTORY)
if(NOT hasParent)
    project(UtilsCPP LANGUAGES CXX)
endif()

enable_testing()
    
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(UTILSCPP_BUILD_TESTS "Build utils cpp test executables" OFF)

if(BUILD_SHARED_LIBS)
    add_library(UtilsCPP SHARED)
else()
    add_library(UtilsCPP STATIC)
endif()

file(GLOB_RECURSE UTILSCPP_SRC "src/*.cpp" "src/*.tpp" "include/*.tpp" "src/*.hpp" "include/*.hpp")
target_sources(UtilsCPP PRIVATE ${UTILSCPP_SRC})
target_include_directories(UtilsCPP PRIVATE "src" PUBLIC "include")

if (ENABLE_LLVM_SOURCE_BASED_CODE_COVERAGE)
    target_compile_options(UtilsCPP PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    target_link_options(UtilsCPP    PRIVATE -fprofile-instr-generate -fcoverage-mapping)
endif()

if (ENABLE_LLVM_FSANITIZER)
    target_compile_options(UtilsCPP PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -fno-optimize-sibling-calls)
    target_link_options(UtilsCPP    PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -fno-optimize-sibling-calls)
endif()

if (UTILSCPP_BUILD_TESTS)
    add_subdirectory(tests)
endif()