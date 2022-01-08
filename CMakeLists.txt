cmake_minimum_required (VERSION 3.15)
set(PROJECT_NAME "RTIOW.cpp")
project (${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX)
include(FetchContent)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

set(CMAKE_CXX_SYSROOT_FLAG_CODE "list(APPEND CMAKE_CXX_SOURCE_FILE_EXTENSIONS ixx)")
message("CMAKE_CXX_SOURCE_FILE_EXTENSIONS ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS}")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

FetchContent_Declare(
  sdl2
  GIT_REPOSITORY https://github.com/spurious/SDL-mirror
  GIT_TAG origin/release-2.0.14
)
FetchContent_MakeAvailable(sdl2)

add_executable(${PROJECT_NAME} 
"src/main.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2 SDL2main)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME} PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX /permissive- /Z7 /MT /MP /Bt+>)
target_compile_definitions(${PROJECT_NAME} PUBLIC SEQUENTIAL_PROCESSING=0)
set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
