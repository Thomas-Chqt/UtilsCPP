# ---------------------------------------------------
# CMakeLists.txt
#
# Author: Thomas Choquet <thomas.publique@icloud.com>
# Date: 2024/04/22 13:35:56
# ---------------------------------------------------

cmake_minimum_required(VERSION 3.16)

enable_testing()

option(BUILD_SHARED_LIBS    "Build using shared libraries"    OFF)
option(UTILSCPP_BUILD_TESTS "Build UtilsCPP tests"            OFF)
option(UTILSCPP_INSTALL     "Enable UtilsCPP install command" ON)

if(BUILD_SHARED_LIBS)
    set(UTILSCPP_API_EXPORT ON CACHE BOOL "Export all the symbols" FORCE)
else()
    option(UTILSCPP_API_EXPORT "Export all the symbols" OFF)
endif()

project(UtilsCPP)
enable_language(CXX)

add_library(UtilsCPP)

set_target_properties(UtilsCPP
    PROPERTIES CXX_STANDARD 11
    CXX_STANDARD_REQUIRED   ON
    CXX_VISIBILITY_PRESET   hidden
)

file(GLOB_RECURSE UTILSCPP_SRC "src/*" "include/*")
target_sources(UtilsCPP PRIVATE ${UTILSCPP_SRC})

target_include_directories(UtilsCPP PRIVATE "src" PUBLIC "include")

if(UTILSCPP_API_EXPORT)
    target_compile_definitions(UtilsCPP PRIVATE "UTILSCPP_API_EXPORT")
endif()
if(BUILD_SHARED_LIBS)
    target_compile_definitions(UtilsCPP INTERFACE "UTILSCPP_API_IMPORT")
endif()

if (UTILSCPP_BUILD_TESTS AND NOT (BUILD_SHARED_LIBS AND WIN32))
    add_subdirectory(tests)
endif()

if(UTILSCPP_INSTALL)
    install(TARGETS UtilsCPP
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib"
    )
    install(DIRECTORY "include/" DESTINATION "include")
endif()