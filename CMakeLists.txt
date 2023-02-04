cmake_minimum_required(VERSION 3.24)
project(Ava VERSION 1.0.0 LANGUAGES C)

configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_C_STANDARD 99)

find_package(CURL REQUIRED)
find_package(LibXml2 REQUIRED)

set(INCLUDE_FILES
        include/getting_html.h
        include/global.h
        include/htmlparsing.h
        include/save_to_file.h)

set(SOURCE_FILES
        src/ava.c
        src/ava.h
        src/getting_html.c
        src/getting_html.h
        src/htmlparsing.c
        src/htmlparsing.h
        src/save_to_file.c
        src/global.c
        )

set(TEST_FILES
        test/offline_doc.c
        test/offline_doc.h)

add_executable(Ava
        ${SOURCE_FILES}
        ${INCLUDE_FILES}
        ${TEST_FILES})

target_include_directories(Ava PUBLIC include test)

target_include_directories(Ava PRIVATE ${LIBXML2_INCLUDE_DIR})
target_link_libraries(Ava PRIVATE curl ${LIBXML2_LIBRARIES})
