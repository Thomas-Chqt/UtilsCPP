# ---------------------------------------------------
# CMakeLists.txt
#
# Author: Thomas Choquet <thomas.publique@icloud.com>
# Date: 2024/04/22 04:14:49
# ---------------------------------------------------

include(FetchContent)
include(GoogleTest)

add_executable(UtilsCPP_test)

set_target_properties(UtilsCPP_test PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    FOLDER "tests"
)


file(GLOB_RECURSE UTILSCPP_TEST_SRC "*.cpp" "*.tpp" "*.hpp")
target_sources(UtilsCPP_test PRIVATE ${UTILSCPP_TEST_SRC})

target_include_directories(UtilsCPP_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(UtilsCPP_test PRIVATE UtilsCPP)

set(BUILD_GMOCK OFF)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG main)
FetchContent_MakeAvailable(googletest)
set_target_properties(gtest PROPERTIES FOLDER "dependencies")
set_target_properties(gtest_main PROPERTIES FOLDER "dependencies")
target_link_libraries(UtilsCPP_test PRIVATE GTest::gtest_main)


gtest_discover_tests(UtilsCPP_test)