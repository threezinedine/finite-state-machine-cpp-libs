#pragma once
#include <fsm.hpp>


STATE_ON_ENTRY_DEFINE(parentState)
    std::cout << "On Entry" << std::endl;
STATE_ON_ENTRY_DEFINE_END(parentState)

STATE_ON_RUN_DEFINE(parentState)
    std::cout << "On Run" << std::endl;
STATE_ON_RUN_DEFINE_END(parentState)