cmake_minimum_required(VERSION 3.5)

add_library("CCollectionCore" STATIC "vector.c")

target_include_directories("CCollectionCore" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

