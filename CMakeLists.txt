# ---------------------------------------------------
# CMakeLists.txt
#
# Author: Thomas Choquet <thomas.publique@icloud.com>
# Date: 2024/04/22 13:35:56
# ---------------------------------------------------

cmake_minimum_required(VERSION 3.16)

option(BUILD_SHARED_LIBS "Build using shared libraries"    OFF)

option(UTL_BUILD_TESTS   "Build UtilsCPP tests"            OFF)
if(UTL_BUILD_TESTS)
    option(UTL_BUILD_LEGACY_TESTS "Build legacy tests" ON)
endif()
option(UTL_INSTALL       "Enable UtilsCPP install command" ON)
option(UTL_API_EXPORT    "Export the api symbols"          OFF)

if(BUILD_SHARED_LIBS)
    set(UTL_API_EXPORT ON CACHE BOOL "Export the api symbols" FORCE)
endif()

if(UTL_BUILD_TESTS AND (BUILD_SHARED_LIBS OR UTL_LIB_TYPE STREQUAL "SHARED") AND WIN32)
    message(WARNING "Tests cannot be enable on windows when BUILD_SHARED_LIBS is ON. Disabling...")
    set(UTL_BUILD_TESTS OFF CACHE BOOL "Build UtilsCPP tests" FORCE)
endif()

if(UTL_BUILD_TESTS)
    enable_testing()
endif()

project(UtilsCPP)
enable_language(CXX)

add_library(UtilsCPP ${UTL_LIB_TYPE}) # Use UTL_LIB_TYPE to override BUILD_SHARED_LIBS for UtilsCPP
 
target_compile_features(UtilsCPP PUBLIC cxx_std_20)
set_target_properties(UtilsCPP PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    CXX_EXTENSIONS        OFF
)

file(GLOB_RECURSE UTL_SRC "src/*" "include/*")
target_sources(UtilsCPP PRIVATE ${UTL_SRC})

target_include_directories(UtilsCPP PRIVATE "src" PUBLIC "include")

if(UTL_API_EXPORT)
    target_compile_definitions(UtilsCPP PRIVATE "UTL_API_EXPORT")
endif()
if(BUILD_SHARED_LIBS)
    target_compile_definitions(UtilsCPP INTERFACE "UTL_API_IMPORT")
endif()

if(UTL_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(UTL_INSTALL)
    install(TARGETS UtilsCPP
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib"
    )
    install(DIRECTORY "include/" DESTINATION "include")
endif()
