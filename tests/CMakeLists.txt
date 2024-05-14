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

if (ENABLE_LLVM_SOURCE_BASED_CODE_COVERAGE)
    target_compile_options(UtilsCPP_test PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    target_link_options(UtilsCPP_test PRIVATE -fprofile-instr-generate -fcoverage-mapping)
endif()

if (ENABLE_LLVM_FSANITIZER)
    target_compile_options(UtilsCPP_test PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -fno-optimize-sibling-calls)
    target_link_options(UtilsCPP_test    PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -fno-optimize-sibling-calls)
endif()


target_link_libraries(UtilsCPP_test PRIVATE UtilsCPP)

FetchContent_MakeAvailable(googletest)
target_link_libraries(UtilsCPP_test PRIVATE GTest::gtest_main)

gtest_discover_tests(UtilsCPP_test)