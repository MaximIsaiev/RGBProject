cmake_minimum_required(VERSION 3.5)

project(tddProject LANGUAGES CXX)

if(UNITTEST)
	add_subdirectory(googletests/)
endif()

add_subdirectory(TestTask/libs/printer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(tddProject main.cpp)

target_link_libraries(${PROJECT_NAME} Printer)

