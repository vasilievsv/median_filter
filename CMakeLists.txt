cmake_minimum_required(VERSION 3.5)

project(median CXX)
set(CMAKE_CXX_STANDARD 11)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

    set(LIB_SRC
        ${SRC_DIR}/median.cpp)

    add_library(median STATIC ${LIB_SRC} ${SRC_DIR})
    target_include_directories(median
        PRIVATE
        "$SRC_DIR"
        "${SRC_DIR}/inc"
        PUBLIC
        $<INSTALL_INTERFACE:inc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    )
    set_target_properties(median PROPERTIES OUTPUT_NAME median)

    option(BUILD_TESTING "Build and run tests" ON)
    if (${BUILD_TESTING})
        enable_testing()
        add_subdirectory(tests)
        endif()