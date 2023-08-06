#pragma once
#include <fsm.hpp>


STATE_ON_ENTRY_DEFINE(firstChildState)
    std::cout << "On Entry firstChildState" << std::endl;
STATE_ON_ENTRY_DEFINE_END(firstChildState)

STATE_ON_RUN_DEFINE(firstChildState)
    std::cout << "On Run firstChildState" << std::endl;
STATE_ON_RUN_DEFINE_END(firstChildState)