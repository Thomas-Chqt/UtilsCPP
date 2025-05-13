# ---------------------------------------------------
# CMakeLists.txt
#
# Author: Thomas Choquet <thomas.publique@icloud.com>
# Date: 2024/04/22 04:14:49
# ---------------------------------------------------

include(FetchContent)
include(GoogleTest)

add_executable(UtilsCPP_test)

target_compile_features(UtilsCPP_test PUBLIC cxx_std_20)
set_target_properties(UtilsCPP_test PROPERTIES FOLDER "tests")

file(GLOB_RECURSE UTL_TEST_SRC "*.cpp" "*.hpp" "*.tpp")
target_sources(UtilsCPP_test PRIVATE ${UTL_TEST_SRC})

target_include_directories(UtilsCPP_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
    GIT_SHALLOW    1
)
set(BUILD_GMOCK       OFF)
set(INSTALL_GTEST     OFF)
set(BUILD_SHARED_LIBS OFF)
FetchContent_MakeAvailable(googletest)
set_target_properties(gtest PROPERTIES FOLDER "dependencies")
set_target_properties(gtest_main PROPERTIES FOLDER "dependencies")

target_link_libraries(UtilsCPP_test PRIVATE UtilsCPP GTest::gtest_main)

gtest_discover_tests(UtilsCPP_test)

if(UTL_BUILD_LEGACY_TESTS)
    add_subdirectory(legacy)
endif()
