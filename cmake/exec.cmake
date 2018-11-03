file(REMOVE ${OUT_FILE})
execute_process( 
    COMMAND ${EXECUTABLE} 
    INPUT_FILE ${IN_FILE} 
    OUTPUT_FILE ${OUT_FILE})



