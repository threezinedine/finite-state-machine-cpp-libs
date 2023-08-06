set(
    TEST_PROJECT
    tests
)

file(
    GLOB
    TEST_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)


add_executable(
    ${TEST_PROJECT}
    ${TEST_FILES}
)

target_link_libraries(
    ${TEST_PROJECT}
    gtest
    gmock
    fsm_lib
)

target_include_directories(
    ${TEST_PROJECT}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)