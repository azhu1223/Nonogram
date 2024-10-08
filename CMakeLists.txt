cmake_minimum_required(VERSION 3.30.3)
project(nonogram)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Make sure developers do not run cmake in the main project directory, to keep
# build artifacts from becoming clutter
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
message(FATAL_ERROR "In-source builds not allowed.
Please make a new directory (called a build directory) and run
CMake from there.You may need to remove CMakeCache.txt." )
endif()

# Check if the build type is set for coverage
if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    message(STATUS "Configuring build for coverage")
    # Add flags for GCC to generate coverage data
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

include(GoogleTest)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(include)

# Libraries
add_library(Board_lib src/Board.cpp)
add_library(Game_lib src/Game.cpp)

target_link_libraries(Game_lib
                    Board_lib)

add_executable(nonogram src/main.cpp)

target_link_libraries(nonogram
                    Game_lib)

add_executable(Board_test tests/BoardTest.cpp)

target_link_libraries(Board_test 
                      Board_lib
                      gtest_main)

gtest_discover_tests(Board_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)
