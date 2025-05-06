cmake_minimum_required(VERSION 3.14)
include(cfg.cmake)

FIND_PROGRAM( GCOV_PATH gcov )
FIND_PROGRAM( LCOV_PATH lcov )
FIND_PROGRAM( GENHTML_PATH genhtml )
FIND_PROGRAM( GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR})

IF(NOT GCOV_PATH)
	MESSAGE(FATAL_ERROR "gcov not found! Aborting...
  Run: sudo apt-get install gcov")
ENDIF() 

IF(NOT LCOV_PATH)
	MESSAGE(FATAL_ERROR "lcov not found! Aborting...
  Run: sudo apt-get install lcov")
ENDIF() 

IF(NOT GENHTML_PATH)
	MESSAGE(FATAL_ERROR "genhtml not found! Aborting...
  Run: sudo apt-get install lcov")
ENDIF() 

IF(NOT GCOVR_PATH)
	MESSAGE(FATAL_ERROR "gcovr not found! Aborting...
  Run: sudo apt-get install gcovr")
ENDIF() 

project(testBase LANGUAGES CXX C)

# Set build configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-g3 -Wall -Wextra --coverage -fprofile-arcs -ftest-coverage -O0")
set(CMAKE_CXX_FLAGS "-g3 -Wall -Wextra -std=c++11 --coverage -fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov --coverage")

# Create directory if not exist
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/out)
# Set folder output configuration
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/out)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}) 

include(FetchContent)
# Download and make GoogleTest available
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Enable test discovery with CTest
enable_testing()

# Add the main cmake folder
add_subdirectory(ut)
