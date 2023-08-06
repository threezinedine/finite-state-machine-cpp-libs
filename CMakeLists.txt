cmake_minimum_required(VERSION 3.10)

project(
    FSM_Project
    VERSION 1.0
)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fsm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)