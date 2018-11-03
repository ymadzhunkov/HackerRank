add_custom_target(run_all_unit_tests ALL)
function(add_unit_test)
    cmake_parse_arguments(ARG 
        "" 
        "PROJECT_NAME" 
        "SOURCES;TEST_SOURCES;LINK_LIBS" 
        ${ARGN}
    )
    set(UNIT_TESTS ${ARG_PROJECT_NAME}_tests)
    add_executable(${UNIT_TESTS} ${ARG_TEST_SOURCES} ${ARG_SOURCES})
    target_link_libraries(${UNIT_TESTS} ${ARG_LINK_LIBS} doctest_with_main)

    set(OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/${UNIT_TESTS}.log)
    add_custom_command(
        OUTPUT ${OUTPUT_FILE}
        COMMAND $<TARGET_FILE:${UNIT_TESTS}> --force-colors=true 
        COMMAND ${CMAKE_COMMAND} -DOUTPUT_FILE=${OUTPUT_FILE} -P ${CMAKE_SOURCE_DIR}/cmake/timestamp.cmake 
        DEPENDS ${UNIT_TESTS}
    )

    add_custom_target(run_${UNIT_TESTS} DEPENDS ${OUTPUT_FILE})
    add_dependencies(run_all_unit_tests run_${UNIT_TESTS})
endfunction()
