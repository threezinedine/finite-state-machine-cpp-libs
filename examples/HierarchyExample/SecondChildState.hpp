#pragma once
#include <fsm.hpp>


STATE_ON_ENTRY_DEFINE(secondChildState)
    std::cout << "On Entry secondChildState" << std::endl;
STATE_ON_ENTRY_DEFINE_END(secondChildState)

STATE_ON_RUN_DEFINE(secondChildState)
    std::cout << "On Run secondChildState" << std::endl;
STATE_ON_RUN_DEFINE_END(secondChildState)