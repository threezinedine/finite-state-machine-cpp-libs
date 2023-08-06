#pragma once
#include <fsm.hpp>


STATE_ON_ENTRY_DEFINE(secondFirstChildState)
    std::cout << "On Entry secondFirstChildState" << std::endl;
STATE_ON_ENTRY_DEFINE_END(secondFirstChildState)

STATE_ON_RUN_DEFINE(secondFirstChildState)
    std::cout << "On Run secondFirstChildState" << std::endl;
STATE_ON_RUN_DEFINE_END(secondFirstChildState)