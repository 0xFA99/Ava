cmake_minimum_required(VERSION 3.24)
project(Ava VERSION 1.0.0 LANGUAGES C)

configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_C_STANDARD 99)

find_package(CURL REQUIRED)
find_package(LibXml2 REQUIRED)


set(INCLUDE_FILES
        include/getting_html.h
        include/global.h)

set(SOURCE_FILES
        src/ava.c
        src/ava.h
        src/getting_html.c
        src/getting_html.h
        src/global.c include/save_to_file.h src/save_to_file.c include/htmlparsing.h include/output.h)

add_executable(Ava
        ${SOURCE_FILES}
        ${INCLUDE_FILES})

target_include_directories(Ava PUBLIC include)

target_include_directories(Ava PRIVATE ${LIBXML2_INCLUDE_DIR})
target_link_libraries(Ava PRIVATE curl ${LIBXML2_LIBRARIES})
