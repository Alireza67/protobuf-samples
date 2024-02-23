cmake_minimum_required(VERSION 3.22.1)
project(protobuf-samples LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(SOURCE protobuf-samples/baseFeatures.cpp)
list(APPEND SOURCE protobuf-samples/pch.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

find_package(Protobuf REQUIRED)
protobuf_generate_cpp(protobuf-samples/ protobuf-samples/ protobuf-samples/protos/)
include_directories(${Protobuf_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Protobuf_LIBRARIES})


find_package(GTest REQUIRED COMPONENTS gtest_main gtest_static)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest::gtest_main)

enable_testing()
include(GoogleTest)
