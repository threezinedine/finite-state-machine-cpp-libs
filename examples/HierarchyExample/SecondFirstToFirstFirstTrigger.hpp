#pragma once
#include <fsm.hpp>
#include "FirstFirstChildState.hpp"
#include "SecondFirstChildState.hpp"


TRIGGER_DEFINE(secondFirstChildState, firstFirstChildState)
    return true;
TRIGGER_DEFINE_END(secondFirstChildState, firstFirstChildState)