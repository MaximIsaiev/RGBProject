cmake_minimum_required(VERSION 3.5)

project(tddProject LANGUAGES CXX)

set(UNITTEST ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY   ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/binaries)

if(UNIX)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/binaries/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/binaries/lib)
elseif(WIN32)
    set(TEST_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/binaries)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY   ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/binaries)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/binaries)
endif()

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

if(UNIX)
        add_custom_target( distclean COMMAND find . -name *_automoc.cpp -type f -delete
                COMMAND find . -name moc_*cpp -type f -delete
                COMMAND find . -name *_t -type f -delete
                # This is commented just in case, who knows if this can be the thing that deletes your system.
                # COMMAND rm -rf  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE}/*
                # THIS LITERALLY DELETES THE WHOLE SYSTEM! CAN YOU PLEASE CHECK IF VARS EXIST FIRST!
                # This is so bad I wand to punch (in minecraft) whoever wrote this, already deleted 2 systems
                # A quick search reveals that this var is never set anywhere, in fact it exists here and nowhere else
                # So "rm -rf  ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE}/*" --becomes-> "rm -rf  /*", looks familiar?
                # Thanks a lot.
                # COMMAND rm -rf  ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE}/*
                COMMAND rm -rf ./binnaries/lib/*
                COMMAND rm -rf ./binnaries/plugins/*
                COMMAND rm -rf ./binnaries/tasks/*
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${QBOX_PROJECT_NAME})
endif()


