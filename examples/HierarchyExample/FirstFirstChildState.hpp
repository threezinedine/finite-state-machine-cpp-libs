#pragma once
#include <fsm.hpp>


STATE_ON_ENTRY_DEFINE(firstFirstChildState)
    std::cout << "On Entry firstFirstChildState" << std::endl;
STATE_ON_ENTRY_DEFINE_END(firstFirstChildState)

STATE_ON_RUN_DEFINE(firstFirstChildState)
    std::cout << "On Run firstFirstChildState" << std::endl;
STATE_ON_RUN_DEFINE_END(firstFirstChildState)