cmake_minimum_required(VERSION 3.15)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

# WORKAROUND
# This is added so that CMake can recognize the .ixx extension as a module interface.
set(CMAKE_CXX_SYSROOT_FLAG_CODE "list(APPEND CMAKE_CXX_SOURCE_FILE_EXTENSIONS ixx)")

project(Raycer VERSION 0.1.0 LANGUAGES CXX)

# It is always easier to navigate in an IDE when projects are organized in folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

message("CMAKE_CXX_SOURCE_FILE_EXTENSIONS ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS}")

include(FetchContent)
FetchContent_Declare(
  sdl2
  GIT_REPOSITORY https://github.com/spurious/SDL-mirror
  GIT_TAG origin/release-2.0.14
)
FetchContent_Declare(
  expected
  GIT_REPOSITORY https://github.com/TartanLlama/expected
  GIT_TAG master
)
FetchContent_MakeAvailable(sdl2 expected)

set(H_FILES   includes/SdlInit.h)

set(CPP_FILES src/main.cpp)

add_executable(${PROJECT_NAME} ${CPP_FILES} ${H_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE includes)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2-static SDL2main expected)

# Only support statically linking for now.
target_compile_definitions(${PROJECT_NAME} PRIVATE SEQUENTIAL_PROCESSING=0)

# Require c++20, this is better than setting CMAKE_CXX_STANDARD since it won't pollute other targets
# note : cxx_std_* features were added in CMake 3.8.2
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX /permissive- /Z7 /MP /Bt+>)

set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)