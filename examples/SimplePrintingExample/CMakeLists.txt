set(
    EXAMPLE_FILE
    SimplePrintingExample
)


add_executable(
    ${EXAMPLE_FILE}
    ${EXAMPLE_FILE}.cpp
)


target_link_libraries(
    ${EXAMPLE_FILE}
    fsm_lib
)