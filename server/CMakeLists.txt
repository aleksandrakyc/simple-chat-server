cmake_minimum_required(VERSION 3.0.0)
project(cpp_net_server VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )
    
add_executable(cpp_net_server ${all_SRCS})

