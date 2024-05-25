# ---------------------------------------------------
# CMakeLists.txt
#
# Author: Thomas Choquet <thomas.publique@icloud.com>
# Date: 2024/04/22 04:14:49
# ---------------------------------------------------

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        main
)

add_executable(UtilsCPP_test)

file(GLOB_RECURSE UTILSCPP_TEST_SRC "*.cpp" "*.tpp" "*.hpp")
target_sources(UtilsCPP_test PRIVATE ${UTILSCPP_TEST_SRC})

target_include_directories(UtilsCPP_test PRIVATE ".")

set(BUILD_GMOCK OFF)
FetchContent_MakeAvailable(googletest)
target_link_libraries(UtilsCPP_test UtilsCPP GTest::gtest_main)

gtest_discover_tests(UtilsCPP_test)