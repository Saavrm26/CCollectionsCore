cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/lib")

project("Standard Collection")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG "v1.14.0"
)

FetchContent_MakeAvailable(googletest)

enable_language(C)
enable_language(CXX)

if(CMAKE_BUILD_TYPE EQUAL "Release")
  set(CFLAGS "-Wall -Werror")
else()
  # set(CFLAGS "-ggdb -Wall -fsanitize=address -fdiagnostics-color=always")
  set(CFLAGS "-ggdb -Wall -fdiagnostics-color=always")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CFLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CFLAGS}")

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
