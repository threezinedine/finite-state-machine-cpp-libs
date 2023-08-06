set(
    EXAMPLE_NAME
    HierarchyExample
)

add_executable(
    ${EXAMPLE_NAME}
    ${EXAMPLE_NAME}.cpp
)

target_link_libraries(
    ${EXAMPLE_NAME}
    fsm_lib
)

target_include_directories(
    ${EXAMPLE_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)