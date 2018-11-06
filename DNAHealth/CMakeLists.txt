cmake_minimum_required(VERSION 2.8.12)
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

set(SOURCES 
    src/problem.cpp
    src/CyclicHash.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(${PROJECT_NAME}_main src/main.cpp)
target_link_libraries(${PROJECT_NAME}_main PRIVATE ${PROJECT_NAME}) 

add_executable(generator src/generator.cpp)

foreach(sample 01 02) 
    add_test(NAME ${PROJECT_NAME}_run${sample} COMMAND 
        ${CMAKE_COMMAND} 
        -DEXECUTABLE=$<TARGET_FILE:${PROJECT_NAME}_main>
        -DIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test/sample${sample}.in
        -DOUT_FILE=${CMAKE_CURRENT_BINARY_DIR}/sample${sample}.out
        -P ${CMAKE_SOURCE_DIR}/cmake/exec.cmake
    )
    set_tests_properties(${PROJECT_NAME}_run${sample} PROPERTIES 
        TIMEOUT 3
    ) 

    add_test(
        NAME ${PROJECT_NAME}_check${sample} 
        COMMAND ${CMAKE_COMMAND} -E compare_files 
           ${CMAKE_CURRENT_SOURCE_DIR}/test/sample${sample}.out
           ${CMAKE_CURRENT_BINARY_DIR}/sample${sample}.out
    )
    set_tests_properties(${PROJECT_NAME}_check${sample} 
                         PROPERTIES DEPENDS ${PROJECT_NAME}_run${sample})
endforeach()

add_unit_test(
    PROJECT_NAME ${PROJECT_NAME} 
    TEST_SOURCES
       "test/Range.cpp"
       "test/CyclicHash.cpp"
       "test/Problem.cpp"
    LINK_LIBS ${PROJECT_NAME})

