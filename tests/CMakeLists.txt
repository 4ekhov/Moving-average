cmake_minimum_required(VERSION 3.27)
project(MovingAverage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

# Для Windows: предотвращение переопределения настроек компилятора/линкера
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        moving_average_tests
        TestsMovingAverage.cpp
)

target_link_libraries(
        moving_average_tests
        GTest::gtest_main
)

target_include_directories(moving_average_tests PUBLIC ${PROJECT_SOURCE_DIR}/MALib)

include(GoogleTest)
gtest_discover_tests(moving_average_tests)