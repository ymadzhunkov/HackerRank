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


add_test(NAME ${PROJECT_NAME}_run0 COMMAND 
    ${CMAKE_COMMAND} 
    -DEXECUTABLE=$<TARGET_FILE:${PROJECT_NAME}_main>
    -DIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test/sample01.in
    -DOUT_FILE=${CMAKE_CURRENT_BINARY_DIR}/sample01.out
    -P ${CMAKE_SOURCE_DIR}/cmake/exec.cmake
)
add_test(
    NAME ${PROJECT_NAME}_check0 
    COMMAND ${CMAKE_COMMAND} -E compare_files 
       ${CMAKE_CURRENT_SOURCE_DIR}/test/sample01.out
       ${CMAKE_CURRENT_BINARY_DIR}/sample01.out
)
SET_TESTS_PROPERTIES(${PROJECT_NAME}_check0 
                     PROPERTIES DEPENDS ${PROJECT_NAME}_run0)
add_unit_test(
    PROJECT_NAME ${PROJECT_NAME} 
    TEST_SOURCES
       "test/Range.cpp"
       "test/CyclicHash.cpp"
    LINK_LIBS ${PROJECT_NAME})

