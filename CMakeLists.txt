cmake_minimum_required(VERSION 3.27)
project(gecs VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bib)


include_directories(headers)
add_library(gecs STATIC
    src/gecs.c src/gecs_array.c
        src/gecs_gdata.c
        src/gecs_typedefs.c
        src/gecs_componentgroup.c
        src/gecs_bitset.c
        src/gecs_entityarray.c
)
add_executable(ExampleTest examples/ExampleTest.c)
target_link_libraries(ExampleTest gecs)