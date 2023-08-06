set(
    FSM_LIB
    fsm_lib
)

file(
    GLOB
    SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(
    ${FSM_LIB}
    ${SRC_FILES}
)

target_include_directories(
    ${FSM_LIB}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)