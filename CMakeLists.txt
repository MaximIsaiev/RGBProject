cmake_minimum_required(VERSION 3.5)

project(tddProject LANGUAGES CXX)

set(UNITTEST=ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/binaries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/binaries)


if(UNITTEST)
        add_subdirectory(googletests/)
endif()


add_subdirectory(TestTask/libs/printer)


if(UNITTEST)
        message(" output lib dir " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG})
        enable_testing()
endif()


add_executable(tddProject main.cpp)

target_link_libraries(${PROJECT_NAME} Printer)

