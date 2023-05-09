set(TESTS
    median_int
    median_double
    )

foreach(fname ${TESTS})
    add_executable(test_${fname} test_${fname}.cpp)
    target_include_directories(test_${fname} PRIVATE "${SRC_DIR}")
    target_link_libraries(test_${fname} median)
    add_test(NAME test_${fname} COMMAND $<TARGET_FILE:test_${fname}>)
endforeach()