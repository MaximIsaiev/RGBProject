cmake_minimum_required(VERSION 3.0)

project(gtest)

set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES *.h gmock/src/gmock-all.cc gtest/src/gtest-all.cc)

add_library(${PROJECT_NAME} SHARED ${SOURCES})


include_directories(gmock/include gmock gtest gtest/include)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/gtest/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/gmock/include)
