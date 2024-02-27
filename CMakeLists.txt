cmake_minimum_required(VERSION 3.22.1)
project(protobuf-samples LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(PROTO_FILES protobuf-samples/protos/person.proto)
list(APPEND PROTO_FILES protobuf-samples/protos/check-oneof.proto)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

set(SOURCE protobuf-samples/baseFeatures.cpp)
list(APPEND SOURCE protobuf-samples/pch.cpp)
list(APPEND SOURCE protobuf-samples/json-support.cpp)
list(APPEND SOURCE protobuf-samples/serialization.cpp)
list(APPEND SOURCE protobuf-samples/extensibility.cpp)
list(APPEND SOURCE protobuf-samples/arena.cpp)
list(APPEND SOURCE ${PROTO_SRCS})

add_executable(${PROJECT_NAME} ${SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC protobuf-samples/)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Protobuf_LIBRARIES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest_main)

enable_testing()
include(GoogleTest)