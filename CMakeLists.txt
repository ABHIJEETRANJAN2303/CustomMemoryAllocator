cmake_minimum_required(VERSION 3.16)
project(CustomMemoryAllocator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directory for all headers
include_directories(include)

# Source files
set(SOURCES
    src/MemoryAllocator.cpp
    src/FreeList.cpp
)

# Create the allocator library
add_library(allocator STATIC ${SOURCES})

# Build tests
file(GLOB TEST_FILES tests/*.cpp)

foreach(test_file ${TEST_FILES})
    get_filename_component(test_name ${test_file} NAME_WE)

    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} allocator)
endforeach()
