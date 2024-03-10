cmake_minimum_required(VERSION 3.14)
project(bmstu-cpp-works)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)
#glob all directories who end with _hw
file(GLOB hw_dirs RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/*_hw)
message("homework_dirs: ${hw_dirs}")
foreach (hw_dir ${hw_dirs})
    add_subdirectory(${hw_dir})
endforeach ()
